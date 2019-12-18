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
 int ERANGE ; 
 int /*<<< orphan*/  SOLO_I2C_TW ; 
 int /*<<< orphan*/  TW286x_BRIGHTNESS_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_CONTRAST_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_HUE_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_SATURATIONU_ADDR (int) ; 
 int /*<<< orphan*/  TW286x_SATURATIONV_ADDR (int) ; 
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
 int /*<<< orphan*/  solo_i2c_writebyte (struct solo_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tw_writebyte (struct solo_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char) ; 

int tw28_set_ctrl_val(struct solo_dev *solo_dev, u32 ctrl, u8 ch,
		      s32 val)
{
	char sval;
	u8 chip_num;

	/* Get the right chip and on-chip channel */
	chip_num = ch / 4;
	ch %= 4;

	if (val > 255 || val < 0)
		return -ERANGE;

	switch (ctrl) {
	case V4L2_CID_SHARPNESS:
		/* Only 286x has sharpness */
		if (is_tw286x(solo_dev, chip_num)) {
			u8 v = solo_i2c_readbyte(solo_dev, SOLO_I2C_TW,
						 TW_CHIP_OFFSET_ADDR(chip_num),
						 TW286x_SHARPNESS(chip_num));
			v &= 0xf0;
			v |= val;
			solo_i2c_writebyte(solo_dev, SOLO_I2C_TW,
					   TW_CHIP_OFFSET_ADDR(chip_num),
					   TW286x_SHARPNESS(chip_num), v);
		} else {
			return -EINVAL;
		}
		break;

	case V4L2_CID_HUE:
		if (is_tw286x(solo_dev, chip_num))
			sval = val - 128;
		else
			sval = (char)val;
		tw_writebyte(solo_dev, chip_num, TW286x_HUE_ADDR(ch),
			     TW_HUE_ADDR(ch), sval);

		break;

	case V4L2_CID_SATURATION:
		/* 286x chips have a U and V component for saturation */
		if (is_tw286x(solo_dev, chip_num)) {
			solo_i2c_writebyte(solo_dev, SOLO_I2C_TW,
					   TW_CHIP_OFFSET_ADDR(chip_num),
					   TW286x_SATURATIONU_ADDR(ch), val);
		}
		tw_writebyte(solo_dev, chip_num, TW286x_SATURATIONV_ADDR(ch),
			     TW_SATURATION_ADDR(ch), val);

		break;

	case V4L2_CID_CONTRAST:
		tw_writebyte(solo_dev, chip_num, TW286x_CONTRAST_ADDR(ch),
			     TW_CONTRAST_ADDR(ch), val);
		break;

	case V4L2_CID_BRIGHTNESS:
		if (is_tw286x(solo_dev, chip_num))
			sval = val - 128;
		else
			sval = (char)val;
		tw_writebyte(solo_dev, chip_num, TW286x_BRIGHTNESS_ADDR(ch),
			     TW_BRIGHTNESS_ADDR(ch), sval);

		break;
	default:
		return -EINVAL;
	}

	return 0;
}