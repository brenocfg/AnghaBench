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
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_w1 (struct gspca_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void hv7131r_probe(struct gspca_dev *gspca_dev)
{
	i2c_w1(gspca_dev, 0x02, 0);		/* sensor wakeup */
	msleep(10);
	reg_w1(gspca_dev, 0x02, 0x66);		/* Gpio on */
	msleep(10);
	i2c_r(gspca_dev, 0, 5);			/* read sensor id */
	if (gspca_dev->usb_buf[0] == 0x02	/* chip ID (02 is R) */
	    && gspca_dev->usb_buf[1] == 0x09
	    && gspca_dev->usb_buf[2] == 0x01) {
		gspca_dbg(gspca_dev, D_PROBE, "Sensor HV7131R found\n");
		return;
	}
	pr_warn("Erroneous HV7131R ID 0x%02x 0x%02x 0x%02x\n",
		gspca_dev->usb_buf[0], gspca_dev->usb_buf[1],
		gspca_dev->usb_buf[2]);
}