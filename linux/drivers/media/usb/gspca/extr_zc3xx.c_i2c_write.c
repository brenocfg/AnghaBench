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
struct gspca_dev {scalar_t__ usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static u8 i2c_write(struct gspca_dev *gspca_dev,
			u8 reg,
			u8 valL,
			u8 valH)
{
	u8 retbyte;

	if (gspca_dev->usb_err < 0)
		return 0;
	reg_w(gspca_dev, reg, 0x92);
	reg_w(gspca_dev, valL, 0x93);
	reg_w(gspca_dev, valH, 0x94);
	reg_w(gspca_dev, 0x01, 0x90);		/* <- write command */
	msleep(1);
	retbyte = reg_r(gspca_dev, 0x0091);		/* read status */
	if (retbyte != 0x00)
		pr_err("i2c_w status error %02x\n", retbyte);
	return retbyte;
}