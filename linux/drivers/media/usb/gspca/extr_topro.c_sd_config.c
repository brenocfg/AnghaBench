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
struct usb_device_id {scalar_t__ driver_info; } ;
struct sd {scalar_t__ bridge; int /*<<< orphan*/  framerate; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode_framerates; int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {TYPE_1__ cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BRIDGE_TP6800 ; 
 int /*<<< orphan*/  DEFAULT_FRAME_RATE ; 
 int /*<<< orphan*/  framerates ; 
 int /*<<< orphan*/  framerates_6810 ; 
 int /*<<< orphan*/  vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;

	sd->bridge = id->driver_info;

	gspca_dev->cam.cam_mode = vga_mode;
	gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
	gspca_dev->cam.mode_framerates = sd->bridge == BRIDGE_TP6800 ?
			framerates : framerates_6810;

	sd->framerate = DEFAULT_FRAME_RATE;
	return 0;
}