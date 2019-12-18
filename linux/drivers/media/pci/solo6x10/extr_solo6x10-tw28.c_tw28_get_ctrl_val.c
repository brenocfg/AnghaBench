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
typedef  int u8 ;
typedef  int u32 ;
struct solo_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SOLO_I2C_TW ; 
 int /*<<< orphan*/  TW286x_BRIGHTNESS_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_CONTRAST_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_HUE_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_SATURATIONU_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_SHARPNESS (int) ; 
 int /*<<< orphan*/  TW_BRIGHTNESS_ADDR (int) ; 
 int /*<<< orphan*/  TW_CHIP_OFFSET_ADDR (int) ; 
 int /*<<< orphan*/  TW_CONTRAST_ADDR (int) ; 
 int /*<<< orphan*/  TW_HUE_ADDR (int) ; 
 int /*<<< orphan*/  TW_SATURATION_ADDR (int) ; 
#define  V4L2_CID_BRIGHTNESS 132 
#define  V4L2_CID_CONTRAST 131 
#define  V4L2_CID_HUE 130 
#define  V4L2_CID_SATURATION 129 
#define  V4L2_CID_SHARPNESS 128 
 int /*<<< orphan*/  is_tw286x (struct solo_dev*,int) ; 
 int solo_i2c_readbyte (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* tw_readbyte (struct solo_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tw28_get_ctrl_val(struct solo_dev *solo_dev, u32 ctrl, u8 ch,
		      s32 *val)
{
	u8 rval, chip_num;

	/* Get the right chip and on-chip channel */
	chip_num = ch / 4;
	ch %= 4;

	switch (ctrl) {
	case V4L2_CID_SHARPNESS:
		/* Only 286x has sharpness */
		if (is_tw286x(solo_dev, chip_num)) {
			rval = solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
						 TW_CHIP_OFFSET_ADDR(chip_num),
						 TW286x_SHARPNESS(chip_num));
			*val = rval & 0x0f;
		} else
			*val = 0;
		break;
	case V4L2_CID_HUE:
		rval = tw_readbyte(solo_dev, chip_num, TW286x_HUE_ADDR(ch),
				   TW_HUE_ADDR(ch));
		if (is_tw286x(solo_dev, chip_num))
			*val = (s32)((char)rval) + 128;
		else
			*val = rval;
		break;
	case V4L2_CID_SATURATION:
		*val = tw_readbyte(solo_dev, chip_num,
				   TW286x_SATURATIONU_ADDR(ch),
				   TW_SATURATION_ADDR(ch));
		break;
	case V4L2_CID_CONTRAST:
		*val = tw_readbyte(solo_dev, chip_num,
				   TW286x_CONTRAST_ADDR(ch),
				   TW_CONTRAST_ADDR(ch));
		break;
	case V4L2_CID_BRIGHTNESS:
		rval = tw_readbyte(solo_dev, chip_num,
				   TW286x_BRIGHTNESS_ADDR(ch),
				   TW_BRIGHTNESS_ADDR(ch));
		if (is_tw286x(solo_dev, chip_num))
			*val = (s32)((char)rval) + 128;
		else
			*val = rval;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}