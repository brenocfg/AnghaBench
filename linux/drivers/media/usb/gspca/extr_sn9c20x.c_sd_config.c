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
struct usb_device_id {int driver_info; } ;
struct sd {int sensor; int i2c_addr; int flags; int i2c_intf; int exposure_step; int /*<<< orphan*/  work; scalar_t__ older_step; scalar_t__ old_step; } ;
struct cam {int needs_full_bandwidth; void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SENSOR_HV7131R 133 
#define  SENSOR_MT9M001 132 
#define  SENSOR_MT9M111 131 
#define  SENSOR_MT9M112 130 
#define  SENSOR_OV9650 129 
#define  SENSOR_SOI968 128 
 void* mono_mode ; 
 int /*<<< orphan*/  qual_upd ; 
 void* sxga_mode ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;

	cam = &gspca_dev->cam;
	cam->needs_full_bandwidth = 1;

	sd->sensor = id->driver_info >> 8;
	sd->i2c_addr = id->driver_info;
	sd->flags = id->driver_info >> 16;
	sd->i2c_intf = 0x80;			/* i2c 100 Kb/s */

	switch (sd->sensor) {
	case SENSOR_MT9M112:
	case SENSOR_MT9M111:
	case SENSOR_OV9650:
	case SENSOR_SOI968:
		cam->cam_mode = sxga_mode;
		cam->nmodes = ARRAY_SIZE(sxga_mode);
		break;
	case SENSOR_MT9M001:
		cam->cam_mode = mono_mode;
		cam->nmodes = ARRAY_SIZE(mono_mode);
		break;
	case SENSOR_HV7131R:
		sd->i2c_intf = 0x81;			/* i2c 400 Kb/s */
		/* fall through */
	default:
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
		break;
	}

	sd->old_step = 0;
	sd->older_step = 0;
	sd->exposure_step = 16;

	INIT_WORK(&sd->work, qual_upd);

	return 0;
}