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
struct usb_fpix {int /*<<< orphan*/  work_struct; } ;
struct usb_device_id {int dummy; } ;
struct cam {int nmodes; int bulk; int /*<<< orphan*/  bulk_size; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPIX_MAX_TRANSFER ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dostream ; 
 int /*<<< orphan*/  fpix_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		const struct usb_device_id *id)
{
	struct usb_fpix *dev = (struct usb_fpix *) gspca_dev;
	struct cam *cam = &gspca_dev->cam;

	cam->cam_mode = fpix_mode;
	cam->nmodes = 1;
	cam->bulk = 1;
	cam->bulk_size = FPIX_MAX_TRANSFER;

	INIT_WORK(&dev->work_struct, dostream);

	return 0;
}