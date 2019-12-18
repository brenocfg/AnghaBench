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
struct sd {int stream_flag; scalar_t__ cam_tag; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int xfer_ep; struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  depth_camera_mode ; 

__attribute__((used)) static int sd_config_depth(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	sd->cam_tag = 0;

	sd->stream_flag = 0x70;

	cam = &gspca_dev->cam;

	cam->cam_mode = depth_camera_mode;
	cam->nmodes = ARRAY_SIZE(depth_camera_mode);

	gspca_dev->xfer_ep = 0x82;

	return 0;
}