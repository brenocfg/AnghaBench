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
struct sd {int /*<<< orphan*/  frame_rate; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFAULT_FRAME_RATE ; 
 int /*<<< orphan*/  ov772x_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;

	cam->cam_mode = ov772x_mode;
	cam->nmodes = ARRAY_SIZE(ov772x_mode);

	sd->frame_rate = DEFAULT_FRAME_RATE;

	return 0;
}