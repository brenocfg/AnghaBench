#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct v4l2_ctrl {int dummy; } ;
struct msi2500_dev {unsigned int f_adc; int pixelformat; int /*<<< orphan*/  dev; int /*<<< orphan*/  hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WREG ; 
 unsigned int DIV_LO_OUT ; 
 int DIV_PRE_N ; 
 int F_REF ; 
#define  MSI2500_PIX_FMT_SDR_MSI2500_384 133 
#define  MSI2500_PIX_FMT_SDR_S12 132 
 int /*<<< orphan*/  V4L2_CID_RF_TUNER_BANDWIDTH ; 
 int /*<<< orphan*/  V4L2_CID_RF_TUNER_BANDWIDTH_AUTO ; 
#define  V4L2_SDR_FMT_CS14LE 131 
#define  V4L2_SDR_FMT_CS8 130 
#define  V4L2_SDR_FMT_CU16LE 129 
#define  V4L2_SDR_FMT_CU8 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,unsigned int,...) ; 
 unsigned int div_u64 (int,int) ; 
 unsigned int div_u64_rem (unsigned int,int,unsigned int*) ; 
 int msi2500_ctrl_msg (struct msi2500_dev*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ v4l2_ctrl_g_ctrl (struct v4l2_ctrl*) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (struct v4l2_ctrl*,unsigned int) ; 

__attribute__((used)) static int msi2500_set_usb_adc(struct msi2500_dev *dev)
{
	int ret;
	unsigned int f_vco, f_sr, div_n, k, k_cw, div_out;
	u32 reg3, reg4, reg7;
	struct v4l2_ctrl *bandwidth_auto;
	struct v4l2_ctrl *bandwidth;

	f_sr = dev->f_adc;

	/* set tuner, subdev, filters according to sampling rate */
	bandwidth_auto = v4l2_ctrl_find(&dev->hdl,
			V4L2_CID_RF_TUNER_BANDWIDTH_AUTO);
	if (v4l2_ctrl_g_ctrl(bandwidth_auto)) {
		bandwidth = v4l2_ctrl_find(&dev->hdl,
				V4L2_CID_RF_TUNER_BANDWIDTH);
		v4l2_ctrl_s_ctrl(bandwidth, dev->f_adc);
	}

	/* select stream format */
	switch (dev->pixelformat) {
	case V4L2_SDR_FMT_CU8:
		reg7 = 0x000c9407; /* 504 */
		break;
	case  V4L2_SDR_FMT_CU16LE:
		reg7 = 0x00009407; /* 252 */
		break;
	case V4L2_SDR_FMT_CS8:
		reg7 = 0x000c9407; /* 504 */
		break;
	case MSI2500_PIX_FMT_SDR_MSI2500_384:
		reg7 = 0x0000a507; /* 384 */
		break;
	case MSI2500_PIX_FMT_SDR_S12:
		reg7 = 0x00008507; /* 336 */
		break;
	case V4L2_SDR_FMT_CS14LE:
		reg7 = 0x00009407; /* 252 */
		break;
	default:
		reg7 = 0x000c9407; /* 504 */
		break;
	}

	/*
	 * Fractional-N synthesizer
	 *
	 *           +----------------------------------------+
	 *           v                                        |
	 *  Fref   +----+     +-------+     +-----+         +------+     +---+
	 * ------> | PD | --> |  VCO  | --> | /2  | ------> | /N.F | <-- | K |
	 *         +----+     +-------+     +-----+         +------+     +---+
	 *                      |
	 *                      |
	 *                      v
	 *                    +-------+     +-----+  Fout
	 *                    | /Rout | --> | /12 | ------>
	 *                    +-------+     +-----+
	 */
	/*
	 * Synthesizer config is just a educated guess...
	 *
	 * [7:0]   0x03, register address
	 * [8]     1, power control
	 * [9]     ?, power control
	 * [12:10] output divider
	 * [13]    0 ?
	 * [14]    0 ?
	 * [15]    fractional MSB, bit 20
	 * [16:19] N
	 * [23:20] ?
	 * [24:31] 0x01
	 *
	 * output divider
	 * val   div
	 *   0     - (invalid)
	 *   1     4
	 *   2     6
	 *   3     8
	 *   4    10
	 *   5    12
	 *   6    14
	 *   7    16
	 *
	 * VCO 202000000 - 720000000++
	 */

	#define F_REF 24000000
	#define DIV_PRE_N 2
	#define DIV_LO_OUT 12
	reg3 = 0x01000303;
	reg4 = 0x00000004;

	/* XXX: Filters? AGC? VCO band? */
	if (f_sr < 6000000)
		reg3 |= 0x1 << 20;
	else if (f_sr < 7000000)
		reg3 |= 0x5 << 20;
	else if (f_sr < 8500000)
		reg3 |= 0x9 << 20;
	else
		reg3 |= 0xd << 20;

	for (div_out = 4; div_out < 16; div_out += 2) {
		f_vco = f_sr * div_out * DIV_LO_OUT;
		dev_dbg(dev->dev, "div_out=%u f_vco=%u\n", div_out, f_vco);
		if (f_vco >= 202000000)
			break;
	}

	/* Calculate PLL integer and fractional control word. */
	div_n = div_u64_rem(f_vco, DIV_PRE_N * F_REF, &k);
	k_cw = div_u64((u64) k * 0x200000, DIV_PRE_N * F_REF);

	reg3 |= div_n << 16;
	reg3 |= (div_out / 2 - 1) << 10;
	reg3 |= ((k_cw >> 20) & 0x000001) << 15; /* [20] */
	reg4 |= ((k_cw >>  0) & 0x0fffff) <<  8; /* [19:0] */

	dev_dbg(dev->dev,
		"f_sr=%u f_vco=%u div_n=%u k=%u div_out=%u reg3=%08x reg4=%08x\n",
		f_sr, f_vco, div_n, k, div_out, reg3, reg4);

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00608008);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00000c05);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00020000);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00480102);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, 0x00f38008);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg7);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg4);
	if (ret)
		goto err;

	ret = msi2500_ctrl_msg(dev, CMD_WREG, reg3);
err:
	return ret;
}