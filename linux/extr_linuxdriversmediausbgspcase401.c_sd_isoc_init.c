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
struct gspca_dev {int alt; int usb_err; } ;

/* Variables and functions */

__attribute__((used)) static int sd_isoc_init(struct gspca_dev *gspca_dev)
{
	gspca_dev->alt = 1;	/* Ignore the bogus isoc alt settings */

	return gspca_dev->usb_err;
}