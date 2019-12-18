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
struct gspca_dev {int* usb_buf; int usb_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	int i;

	/*
	 * The konica needs a freaking large time to "boot" (approx 6.5 sec.),
	 * and does not want to be bothered while doing so :|
	 * Register 0x10 counts from 1 - 3, with 3 being "ready"
	 */
	msleep(6000);
	for (i = 0; i < 20; i++) {
		reg_r(gspca_dev, 0, 0x10);
		if (gspca_dev->usb_buf[0] == 3)
			break;
		msleep(100);
	}
	reg_w(gspca_dev, 0, 0x0d);

	return gspca_dev->usb_err;
}