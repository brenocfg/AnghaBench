#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_device_id {int dummy; } ;
struct TYPE_2__ {int bulk_nurbs; int bulk; int /*<<< orphan*/  bulk_size; scalar_t__ no_urb_create; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BULK_SIZE ; 
 int /*<<< orphan*/  vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);

	/* Yes we want URBs and we want them now! */
	gspca_dev->cam.no_urb_create = 0;
	gspca_dev->cam.bulk_nurbs = 4;
	/* Largest size the windows driver uses */
	gspca_dev->cam.bulk_size = BULK_SIZE;
	/* Def need to use bulk transfers */
	gspca_dev->cam.bulk = 1;

	return 0;
}