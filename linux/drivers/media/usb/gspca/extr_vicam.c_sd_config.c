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
struct usb_device_id {int dummy; } ;
struct sd {int /*<<< orphan*/  work_struct; } ;
struct cam {int bulk; int bulk_size; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vicam_dostream ; 
 int /*<<< orphan*/  vicam_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		const struct usb_device_id *id)
{
	struct cam *cam = &gspca_dev->cam;
	struct sd *sd = (struct sd *)gspca_dev;

	/* We don't use the buffer gspca allocates so make it small. */
	cam->bulk = 1;
	cam->bulk_size = 64;
	cam->cam_mode = vicam_mode;
	cam->nmodes = ARRAY_SIZE(vicam_mode);

	INIT_WORK(&sd->work_struct, vicam_dostream);

	return 0;
}