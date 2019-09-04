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
struct usb_device_id {int /*<<< orphan*/  driver_info; } ;
struct sd {int /*<<< orphan*/  quality; int /*<<< orphan*/  type; } ;
struct cam {int bulk; int bulk_nurbs; int /*<<< orphan*/  bulk_size; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JEILINJ_MAX_TRANSFER ; 
 int /*<<< orphan*/  QUALITY_DEF ; 
 int /*<<< orphan*/  jlj_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		const struct usb_device_id *id)
{
	struct cam *cam = &gspca_dev->cam;
	struct sd *dev  = (struct sd *) gspca_dev;

	dev->type = id->driver_info;
	dev->quality = QUALITY_DEF;

	cam->cam_mode = jlj_mode;
	cam->nmodes = ARRAY_SIZE(jlj_mode);
	cam->bulk = 1;
	cam->bulk_nurbs = 1;
	cam->bulk_size = JEILINJ_MAX_TRANSFER;
	return 0;
}