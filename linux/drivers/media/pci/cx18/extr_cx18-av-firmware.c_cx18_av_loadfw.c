#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct firmware {int size; scalar_t__* data; } ;
struct TYPE_3__ {struct v4l2_subdev sd; } ;
struct cx18 {TYPE_2__* pci_dev; TYPE_1__ av_state; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CX18_AI1_MUX_843_I2S ; 
 int CX18_AI1_MUX_I2S1 ; 
 int CX18_AI1_MUX_INVALID ; 
 int CX18_AI1_MUX_MASK ; 
 int /*<<< orphan*/  CX18_AUDIO_ENABLE ; 
 int /*<<< orphan*/  CX18_ERR_DEV (struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX18_INFO_DEV (struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int) ; 
 int CX18_MAX_MMIO_WR_RETRIES ; 
 int CXADEC_CHIP_CTRL ; 
 int CXADEC_DL_CTL ; 
 int CXADEC_I2S_IN_CTL ; 
 int CXADEC_I2S_OUT_CTL ; 
 int CXADEC_PIN_CFG3 ; 
 int /*<<< orphan*/  CXADEC_PIN_CTRL1 ; 
 int CXADEC_STD_DET_CTL ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  FWFILE ; 
 int /*<<< orphan*/  cx18_av_and_or4 (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cx18_av_read4 (struct cx18*,int) ; 
 scalar_t__ cx18_av_verifyfw (struct cx18*,struct firmware const*) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write4_expect (struct cx18*,int,int,int,int) ; 
 int /*<<< orphan*/  cx18_av_write4_noretry (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write_expect (struct cx18*,int,int,int,int) ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 scalar_t__ request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

int cx18_av_loadfw(struct cx18 *cx)
{
	struct v4l2_subdev *sd = &cx->av_state.sd;
	const struct firmware *fw = NULL;
	u32 size;
	u32 u, v;
	const u8 *ptr;
	int i;
	int retries1 = 0;

	if (request_firmware(&fw, FWFILE, &cx->pci_dev->dev) != 0) {
		CX18_ERR_DEV(sd, "unable to open firmware %s\n", FWFILE);
		return -EINVAL;
	}

	/* The firmware load often has byte errors, so allow for several
	   retries, both at byte level and at the firmware load level. */
	while (retries1 < 5) {
		cx18_av_write4_expect(cx, CXADEC_CHIP_CTRL, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */
		cx18_av_write_expect(cx, CXADEC_STD_DET_CTL, 0xf6, 0xf6, 0xff);

		/* Reset the Mako core, Register is alias of CXADEC_CHIP_CTRL */
		cx18_av_write4_expect(cx, 0x8100, 0x00010000,
					  0x00008430, 0xffffffff); /* cx25843 */

		/* Put the 8051 in reset and enable firmware upload */
		cx18_av_write4_noretry(cx, CXADEC_DL_CTL, 0x0F000000);

		ptr = fw->data;
		size = fw->size;

		for (i = 0; i < size; i++) {
			u32 dl_control = 0x0F000000 | i | ((u32)ptr[i] << 16);
			u32 value = 0;
			int retries2;
			int unrec_err = 0;

			for (retries2 = 0; retries2 < CX18_MAX_MMIO_WR_RETRIES;
			     retries2++) {
				cx18_av_write4_noretry(cx, CXADEC_DL_CTL,
						       dl_control);
				udelay(10);
				value = cx18_av_read4(cx, CXADEC_DL_CTL);
				if (value == dl_control)
					break;
				/* Check if we can correct the byte by changing
				   the address.  We can only write the lower
				   address byte of the address. */
				if ((value & 0x3F00) != (dl_control & 0x3F00)) {
					unrec_err = 1;
					break;
				}
			}
			if (unrec_err || retries2 >= CX18_MAX_MMIO_WR_RETRIES)
				break;
		}
		if (i == size)
			break;
		retries1++;
	}
	if (retries1 >= 5) {
		CX18_ERR_DEV(sd, "unable to load firmware %s\n", FWFILE);
		release_firmware(fw);
		return -EIO;
	}

	cx18_av_write4_expect(cx, CXADEC_DL_CTL,
				0x03000000 | fw->size, 0x03000000, 0x13000000);

	CX18_INFO_DEV(sd, "loaded %s firmware (%d bytes)\n", FWFILE, size);

	if (cx18_av_verifyfw(cx, fw) == 0)
		cx18_av_write4_expect(cx, CXADEC_DL_CTL,
				0x13000000 | fw->size, 0x13000000, 0x13000000);

	/* Output to the 416 */
	cx18_av_and_or4(cx, CXADEC_PIN_CTRL1, ~0, 0x78000);

	/* Audio input control 1 set to Sony mode */
	/* Audio output input 2 is 0 for slave operation input */
	/* 0xC4000914[5]: 0 = left sample on WS=0, 1 = left sample on WS=1 */
	/* 0xC4000914[7]: 0 = Philips mode, 1 = Sony mode (1st SCK rising edge
	   after WS transition for first bit of audio word. */
	cx18_av_write4(cx, CXADEC_I2S_IN_CTL, 0x000000A0);

	/* Audio output control 1 is set to Sony mode */
	/* Audio output control 2 is set to 1 for master mode */
	/* 0xC4000918[5]: 0 = left sample on WS=0, 1 = left sample on WS=1 */
	/* 0xC4000918[7]: 0 = Philips mode, 1 = Sony mode (1st SCK rising edge
	   after WS transition for first bit of audio word. */
	/* 0xC4000918[8]: 0 = slave operation, 1 = master (SCK_OUT and WS_OUT
	   are generated) */
	cx18_av_write4(cx, CXADEC_I2S_OUT_CTL, 0x000001A0);

	/* set alt I2s master clock to /0x16 and enable alt divider i2s
	   passthrough */
	cx18_av_write4(cx, CXADEC_PIN_CFG3, 0x5600B687);

	cx18_av_write4_expect(cx, CXADEC_STD_DET_CTL, 0x000000F6, 0x000000F6,
								  0x3F00FFFF);
	/* CxDevWrReg(CXADEC_STD_DET_CTL, 0x000000FF); */

	/* Set bit 0 in register 0x9CC to signify that this is MiniMe. */
	/* Register 0x09CC is defined by the Merlin firmware, and doesn't
	   have a name in the spec. */
	cx18_av_write4(cx, 0x09CC, 1);

	v = cx18_read_reg(cx, CX18_AUDIO_ENABLE);
	/* If bit 11 is 1, clear bit 10 */
	if (v & 0x800)
		cx18_write_reg_expect(cx, v & 0xFFFFFBFF, CX18_AUDIO_ENABLE,
				      0, 0x400);

	/* Toggle the AI1 MUX */
	v = cx18_read_reg(cx, CX18_AUDIO_ENABLE);
	u = v & CX18_AI1_MUX_MASK;
	v &= ~CX18_AI1_MUX_MASK;
	if (u == CX18_AI1_MUX_843_I2S || u == CX18_AI1_MUX_INVALID) {
		/* Switch to I2S1 */
		v |= CX18_AI1_MUX_I2S1;
		cx18_write_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to the A/V decoder core I2S output */
		v = (v & ~CX18_AI1_MUX_MASK) | CX18_AI1_MUX_843_I2S;
	} else {
		/* Switch to the A/V decoder core I2S output */
		v |= CX18_AI1_MUX_843_I2S;
		cx18_write_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
				      v, CX18_AI1_MUX_MASK);
		/* Switch back to I2S1 or I2S2 */
		v = (v & ~CX18_AI1_MUX_MASK) | u;
	}
	cx18_write_reg_expect(cx, v | 0xb00, CX18_AUDIO_ENABLE,
			      v, CX18_AI1_MUX_MASK);

	/* Enable WW auto audio standard detection */
	v = cx18_av_read4(cx, CXADEC_STD_DET_CTL);
	v |= 0xFF;   /* Auto by default */
	v |= 0x400;  /* Stereo by default */
	v |= 0x14000000;
	cx18_av_write4_expect(cx, CXADEC_STD_DET_CTL, v, v, 0x3F00FFFF);

	release_firmware(fw);
	return 0;
}