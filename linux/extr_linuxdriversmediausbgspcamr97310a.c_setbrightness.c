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
struct sd {scalar_t__ cam_type; scalar_t__ do_lcd_stop; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ CAM_TYPE_VGA ; 
 int /*<<< orphan*/  sensor_write1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 sign_reg = 7;  /* This reg and the next one used on CIF cams. */
	u8 value_reg = 8; /* VGA cams seem to use regs 0x0b and 0x0c */
	static const u8 quick_clix_table[] =
	/*	  0  1  2   3  4  5  6  7  8  9  10  11  12  13  14  15 */
		{ 0, 4, 8, 12, 1, 2, 3, 5, 6, 9,  7, 10, 13, 11, 14, 15};
	if (sd->cam_type == CAM_TYPE_VGA) {
		sign_reg += 4;
		value_reg += 4;
	}

	/* Note register 7 is also seen as 0x8x or 0xCx in some dumps */
	if (val > 0) {
		sensor_write1(gspca_dev, sign_reg, 0x00);
	} else {
		sensor_write1(gspca_dev, sign_reg, 0x01);
		val = 257 - val;
	}
	/* Use lookup table for funky Argus QuickClix brightness */
	if (sd->do_lcd_stop)
		val = quick_clix_table[val];

	sensor_write1(gspca_dev, value_reg, val);
}