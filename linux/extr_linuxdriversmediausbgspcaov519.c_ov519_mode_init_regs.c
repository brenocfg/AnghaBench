#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* cam_mode; } ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_8__ {size_t curr_mode; TYPE_3__ cam; TYPE_1__ pixfmt; } ;
struct sd {int sensor; scalar_t__ frame_rate; int clockdiv; TYPE_4__ gspca_dev; } ;
struct ov_regvals {int member_0; int member_1; } ;
struct gspca_dev {int dummy; } ;
struct TYPE_6__ {scalar_t__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct ov_regvals const*) ; 
 int /*<<< orphan*/  D_STREAM ; 
 int OV519_R10_H_SIZE ; 
 int OV519_R11_V_SIZE ; 
 int OV519_R12_X_OFFSETL ; 
 int OV519_R13_X_OFFSETH ; 
 int OV519_R14_Y_OFFSETL ; 
 int OV519_R15_Y_OFFSETH ; 
 int OV519_R16_DIVIDER ; 
 int /*<<< orphan*/  OV519_R20_DFR ; 
 int OV519_R25_FORMAT ; 
#define  OV519_R54_EN_CLK1 133 
#define  SEN_OV7640 132 
#define  SEN_OV7648 131 
#define  SEN_OV7660 130 
#define  SEN_OV7670 129 
#define  SEN_OV8610 128 
 scalar_t__ frame_rate ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 
 int /*<<< orphan*/  reg_w_mask (struct sd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_regvals (struct sd*,struct ov_regvals const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov519_mode_init_regs(struct sd *sd)
{
	static const struct ov_regvals mode_init_519_ov7670[] = {
		{ 0x5d,	0x03 }, /* Turn off suspend mode */
		{ 0x53,	0x9f }, /* was 9b in 1.65-1.08 */
		{ OV519_R54_EN_CLK1, 0x0f }, /* bit2 (jpeg enable) */
		{ 0xa2,	0x20 }, /* a2-a5 are undocumented */
		{ 0xa3,	0x18 },
		{ 0xa4,	0x04 },
		{ 0xa5,	0x28 },
		{ 0x37,	0x00 },	/* SetUsbInit */
		{ 0x55,	0x02 }, /* 4.096 Mhz audio clock */
		/* Enable both fields, YUV Input, disable defect comp (why?) */
		{ 0x20,	0x0c },
		{ 0x21,	0x38 },
		{ 0x22,	0x1d },
		{ 0x17,	0x50 }, /* undocumented */
		{ 0x37,	0x00 }, /* undocumented */
		{ 0x40,	0xff }, /* I2C timeout counter */
		{ 0x46,	0x00 }, /* I2C clock prescaler */
		{ 0x59,	0x04 },	/* new from windrv 090403 */
		{ 0xff,	0x00 }, /* undocumented */
		/* windows reads 0x55 at this point, why? */
	};

	static const struct ov_regvals mode_init_519[] = {
		{ 0x5d,	0x03 }, /* Turn off suspend mode */
		{ 0x53,	0x9f }, /* was 9b in 1.65-1.08 */
		{ OV519_R54_EN_CLK1, 0x0f }, /* bit2 (jpeg enable) */
		{ 0xa2,	0x20 }, /* a2-a5 are undocumented */
		{ 0xa3,	0x18 },
		{ 0xa4,	0x04 },
		{ 0xa5,	0x28 },
		{ 0x37,	0x00 },	/* SetUsbInit */
		{ 0x55,	0x02 }, /* 4.096 Mhz audio clock */
		/* Enable both fields, YUV Input, disable defect comp (why?) */
		{ 0x22,	0x1d },
		{ 0x17,	0x50 }, /* undocumented */
		{ 0x37,	0x00 }, /* undocumented */
		{ 0x40,	0xff }, /* I2C timeout counter */
		{ 0x46,	0x00 }, /* I2C clock prescaler */
		{ 0x59,	0x04 },	/* new from windrv 090403 */
		{ 0xff,	0x00 }, /* undocumented */
		/* windows reads 0x55 at this point, why? */
	};

	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;

	/******** Set the mode ********/
	switch (sd->sensor) {
	default:
		write_regvals(sd, mode_init_519, ARRAY_SIZE(mode_init_519));
		if (sd->sensor == SEN_OV7640 ||
		    sd->sensor == SEN_OV7648) {
			/* Select 8-bit input mode */
			reg_w_mask(sd, OV519_R20_DFR, 0x10, 0x10);
		}
		break;
	case SEN_OV7660:
		return;		/* done by ov519_set_mode/fr() */
	case SEN_OV7670:
		write_regvals(sd, mode_init_519_ov7670,
				ARRAY_SIZE(mode_init_519_ov7670));
		break;
	}

	reg_w(sd, OV519_R10_H_SIZE,	sd->gspca_dev.pixfmt.width >> 4);
	reg_w(sd, OV519_R11_V_SIZE,	sd->gspca_dev.pixfmt.height >> 3);
	if (sd->sensor == SEN_OV7670 &&
	    sd->gspca_dev.cam.cam_mode[sd->gspca_dev.curr_mode].priv)
		reg_w(sd, OV519_R12_X_OFFSETL, 0x04);
	else if (sd->sensor == SEN_OV7648 &&
	    sd->gspca_dev.cam.cam_mode[sd->gspca_dev.curr_mode].priv)
		reg_w(sd, OV519_R12_X_OFFSETL, 0x01);
	else
		reg_w(sd, OV519_R12_X_OFFSETL, 0x00);
	reg_w(sd, OV519_R13_X_OFFSETH,	0x00);
	reg_w(sd, OV519_R14_Y_OFFSETL,	0x00);
	reg_w(sd, OV519_R15_Y_OFFSETH,	0x00);
	reg_w(sd, OV519_R16_DIVIDER,	0x00);
	reg_w(sd, OV519_R25_FORMAT,	0x03); /* YUV422 */
	reg_w(sd, 0x26,			0x00); /* Undocumented */

	/******** Set the framerate ********/
	if (frame_rate > 0)
		sd->frame_rate = frame_rate;

/* FIXME: These are only valid at the max resolution. */
	sd->clockdiv = 0;
	switch (sd->sensor) {
	case SEN_OV7640:
	case SEN_OV7648:
		switch (sd->frame_rate) {
		default:
/*		case 30: */
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0xff);
			break;
		case 25:
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0x1f);
			break;
		case 20:
			reg_w(sd, 0xa4, 0x0c);
			reg_w(sd, 0x23, 0x1b);
			break;
		case 15:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0xff);
			sd->clockdiv = 1;
			break;
		case 10:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0x1f);
			sd->clockdiv = 1;
			break;
		case 5:
			reg_w(sd, 0xa4, 0x04);
			reg_w(sd, 0x23, 0x1b);
			sd->clockdiv = 1;
			break;
		}
		break;
	case SEN_OV8610:
		switch (sd->frame_rate) {
		default:	/* 15 fps */
/*		case 15: */
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0xff);
			break;
		case 10:
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0x1f);
			break;
		case 5:
			reg_w(sd, 0xa4, 0x06);
			reg_w(sd, 0x23, 0x1b);
			break;
		}
		break;
	case SEN_OV7670:		/* guesses, based on 7640 */
		gspca_dbg(gspca_dev, D_STREAM, "Setting framerate to %d fps\n",
			  (sd->frame_rate == 0) ? 15 : sd->frame_rate);
		reg_w(sd, 0xa4, 0x10);
		switch (sd->frame_rate) {
		case 30:
			reg_w(sd, 0x23, 0xff);
			break;
		case 20:
			reg_w(sd, 0x23, 0x1b);
			break;
		default:
/*		case 15: */
			reg_w(sd, 0x23, 0xff);
			sd->clockdiv = 1;
			break;
		}
		break;
	}
}