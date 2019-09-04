#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_2__ {int code; int width; int height; } ;
struct mt9v111_dev {scalar_t__ sysclk; int /*<<< orphan*/  ctrls; TYPE_1__ fmt; struct i2c_client* client; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 unsigned int EINVAL ; 
#define  MEDIA_BUS_FMT_UYVY8_2X8 131 
#define  MEDIA_BUS_FMT_VYUY8_2X8 130 
#define  MEDIA_BUS_FMT_YUYV8_2X8 129 
#define  MEDIA_BUS_FMT_YVYU8_2X8 128 
 int /*<<< orphan*/  MT9V111_CORE_R07_OUT_CTRL ; 
 int /*<<< orphan*/  MT9V111_CORE_R07_OUT_CTRL_SAMPLE ; 
 int /*<<< orphan*/  MT9V111_CORE_R09_PIXEL_INT ; 
 int MT9V111_IFP_DECIMATION_FREEZE ; 
 int /*<<< orphan*/  MT9V111_IFP_R3A_OUTFMT_CTRL2 ; 
 int MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR ; 
 int /*<<< orphan*/  MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_MASK ; 
 int MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC ; 
 int /*<<< orphan*/  MT9V111_IFP_RA5_HPAN ; 
 int /*<<< orphan*/  MT9V111_IFP_RA6_HZOOM ; 
 int /*<<< orphan*/  MT9V111_IFP_RA7_HOUT ; 
 int /*<<< orphan*/  MT9V111_IFP_RA8_VPAN ; 
 int /*<<< orphan*/  MT9V111_IFP_RA9_VZOOM ; 
 int /*<<< orphan*/  MT9V111_IFP_RAA_VOUT ; 
 int /*<<< orphan*/  MT9V111_MAX_CLKIN ; 
 int MT9V111_PIXEL_ARRAY_HEIGHT ; 
 int MT9V111_PIXEL_ARRAY_WIDTH ; 
 int /*<<< orphan*/  MT9V111_R01_CORE ; 
 int /*<<< orphan*/  MT9V111_R01_IFP ; 
 unsigned int __mt9v111_hw_reset (struct mt9v111_dev*) ; 
 unsigned int __mt9v111_sw_reset (struct mt9v111_dev*) ; 
 unsigned int mt9v111_update (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mt9v111_write (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9v111_hw_config(struct mt9v111_dev *mt9v111)
{
	struct i2c_client *c = mt9v111->client;
	unsigned int ret;
	u16 outfmtctrl2;

	/* Force device reset. */
	ret = __mt9v111_hw_reset(mt9v111);
	if (ret == -EINVAL)
		ret = __mt9v111_sw_reset(mt9v111);
	if (ret)
		return ret;

	/* Configure internal clock sample rate. */
	ret = mt9v111->sysclk < DIV_ROUND_CLOSEST(MT9V111_MAX_CLKIN, 2) ?
				mt9v111_update(c, MT9V111_R01_CORE,
					MT9V111_CORE_R07_OUT_CTRL,
					MT9V111_CORE_R07_OUT_CTRL_SAMPLE, 1) :
				mt9v111_update(c, MT9V111_R01_CORE,
					MT9V111_CORE_R07_OUT_CTRL,
					MT9V111_CORE_R07_OUT_CTRL_SAMPLE, 0);
	if (ret)
		return ret;

	/*
	 * Configure output image format components ordering.
	 *
	 * TODO: IFP block can also output several RGB permutations, we only
	 *	 support YUYV permutations at the moment.
	 */
	switch (mt9v111->fmt.code) {
	case MEDIA_BUS_FMT_YUYV8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC;
			break;
	case MEDIA_BUS_FMT_VYUY8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR;
			break;
	case MEDIA_BUS_FMT_YVYU8_2X8:
			outfmtctrl2 = MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_YC |
				      MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_CBCR;
			break;
	case MEDIA_BUS_FMT_UYVY8_2X8:
	default:
			outfmtctrl2 = 0;
			break;
	}

	ret = mt9v111_update(c, MT9V111_R01_IFP, MT9V111_IFP_R3A_OUTFMT_CTRL2,
			     MT9V111_IFP_R3A_OUTFMT_CTRL2_SWAP_MASK,
			     outfmtctrl2);
	if (ret)
		return ret;

	/*
	 * Do not change default sensor's core configuration:
	 * output the whole 640x480 pixel array, skip 18 columns and 6 rows.
	 *
	 * Instead, control the output image size through IFP block.
	 *
	 * TODO: No zoom&pan support. Currently we control the output image
	 *	 size only through decimation, with no zoom support.
	 */
	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RA5_HPAN,
			    MT9V111_IFP_DECIMATION_FREEZE);
	if (ret)
		return ret;

	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RA8_VPAN,
			    MT9V111_IFP_DECIMATION_FREEZE);
	if (ret)
		return ret;

	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RA6_HZOOM,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    MT9V111_PIXEL_ARRAY_WIDTH);
	if (ret)
		return ret;

	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RA9_VZOOM,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    MT9V111_PIXEL_ARRAY_HEIGHT);
	if (ret)
		return ret;

	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RA7_HOUT,
			    MT9V111_IFP_DECIMATION_FREEZE |
			    mt9v111->fmt.width);
	if (ret)
		return ret;

	ret = mt9v111_write(c, MT9V111_R01_IFP, MT9V111_IFP_RAA_VOUT,
			    mt9v111->fmt.height);
	if (ret)
		return ret;

	/* Apply controls to set auto exp, auto awb and timings */
	ret = v4l2_ctrl_handler_setup(&mt9v111->ctrls);
	if (ret)
		return ret;

	/*
	 * Set pixel integration time to the whole frame time.
	 * This value controls the the shutter delay when running with AE
	 * disabled. If longer than frame time, it affects the output
	 * frame rate.
	 */
	return mt9v111_write(c, MT9V111_R01_CORE, MT9V111_CORE_R09_PIXEL_INT,
			     MT9V111_PIXEL_ARRAY_HEIGHT);
}