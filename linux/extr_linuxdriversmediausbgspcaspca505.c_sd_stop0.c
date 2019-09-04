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
struct gspca_dev {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	if (!gspca_dev->present)
		return;

	/* This maybe reset or power control */
	reg_write(gspca_dev, 0x03, 0x03, 0x20);
	reg_write(gspca_dev, 0x03, 0x01, 0x00);
	reg_write(gspca_dev, 0x03, 0x00, 0x01);
	reg_write(gspca_dev, 0x05, 0x10, 0x01);
	reg_write(gspca_dev, 0x05, 0x11, 0x0f);
}