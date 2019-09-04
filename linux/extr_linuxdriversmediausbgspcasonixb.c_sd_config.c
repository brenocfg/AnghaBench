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
struct usb_device_id {int driver_info; } ;
struct sd {int sensor; int bridge; } ;
struct cam {int npkt; void* nmodes; void* cam_mode; } ;
struct gspca_dev {int* usb_buf; struct cam cam; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENODEV ; 
 int F_SIF ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 TYPE_1__* sensor_data ; 
 void* sif_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	reg_r(gspca_dev, 0x00);
	if (gspca_dev->usb_buf[0] != 0x10)
		return -ENODEV;

	/* copy the webcam info from the device id */
	sd->sensor = id->driver_info >> 8;
	sd->bridge = id->driver_info & 0xff;

	cam = &gspca_dev->cam;
	if (!(sensor_data[sd->sensor].flags & F_SIF)) {
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	} else {
		cam->cam_mode = sif_mode;
		cam->nmodes = ARRAY_SIZE(sif_mode);
	}
	cam->npkt = 36;			/* 36 packets per ISOC message */

	return 0;
}