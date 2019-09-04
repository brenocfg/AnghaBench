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
struct usb_device_id {scalar_t__ driver_info; } ;
struct sd {scalar_t__ subtype; } ;
struct cam {void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 scalar_t__ LogitechClickSmart310 ; 
 void* sif_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;
	sd->subtype = id->driver_info;
	if (sd->subtype != LogitechClickSmart310) {
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	} else {
		cam->cam_mode = sif_mode;
		cam->nmodes = ARRAY_SIZE(sif_mode);
	}
	return 0;
}