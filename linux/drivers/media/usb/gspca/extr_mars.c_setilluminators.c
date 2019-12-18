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
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int) ; 

__attribute__((used)) static void setilluminators(struct gspca_dev *gspca_dev, bool top, bool bottom)
{
	/* both are off if not streaming */
	gspca_dev->usb_buf[0] = 0x22;
	if (top)
		gspca_dev->usb_buf[1] = 0x76;
	else if (bottom)
		gspca_dev->usb_buf[1] = 0x7a;
	else
		gspca_dev->usb_buf[1] = 0x7e;
	reg_w(gspca_dev, 2);
}