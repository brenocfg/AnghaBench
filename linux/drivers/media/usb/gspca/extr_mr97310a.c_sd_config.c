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
struct usb_device_id {int idProduct; } ;
struct sd {int do_lcd_stop; int sensor_type; int adj_colors; int /*<<< orphan*/  cam_type; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {int* usb_buf; struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAM_TYPE_CIF ; 
 int /*<<< orphan*/  CAM_TYPE_VGA ; 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int cam_get_response16 (struct gspca_dev*,int,int) ; 
 int force_sensor_type ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  sd_stopN (struct gspca_dev*) ; 
 int stream_start (struct gspca_dev*) ; 
 int /*<<< orphan*/  vga_mode ; 
 int zero_the_pointer (struct gspca_dev*) ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam;
	int err_code;

	cam = &gspca_dev->cam;
	cam->cam_mode = vga_mode;
	cam->nmodes = ARRAY_SIZE(vga_mode);
	sd->do_lcd_stop = 0;

	/* Several of the supported CIF cameras share the same USB ID but
	 * require different initializations and different control settings.
	 * The same is true of the VGA cameras. Therefore, we are forced
	 * to start the initialization process in order to determine which
	 * camera is present. Some of the supported cameras require the
	 * memory pointer to be set to 0 as the very first item of business
	 * or else they will not stream. So we do that immediately.
	 */
	err_code = zero_the_pointer(gspca_dev);
	if (err_code < 0)
		return err_code;

	err_code = stream_start(gspca_dev);
	if (err_code < 0)
		return err_code;

	/* Now, the query for sensor type. */
	err_code = cam_get_response16(gspca_dev, 0x07, 1);
	if (err_code < 0)
		return err_code;

	if (id->idProduct == 0x0110 || id->idProduct == 0x010e) {
		sd->cam_type = CAM_TYPE_CIF;
		cam->nmodes--;
		/*
		 * All but one of the known CIF cameras share the same USB ID,
		 * but two different init routines are in use, and the control
		 * settings are different, too. We need to detect which camera
		 * of the two known varieties is connected!
		 *
		 * A list of known CIF cameras follows. They all report either
		 * 0200 for type 0 or 0300 for type 1.
		 * If you have another to report, please do
		 *
		 * Name		sd->sensor_type		reported by
		 *
		 * Sakar 56379 Spy-shot	0		T. Kilgore
		 * Innovage		0		T. Kilgore
		 * Vivitar Mini		0		H. De Goede
		 * Vivitar Mini		0		E. Rodriguez
		 * Vivitar Mini		1		T. Kilgore
		 * Elta-Media 8212dc	1		T. Kaiser
		 * Philips dig. keych.	1		T. Kilgore
		 * Trust Spyc@m 100	1		A. Jacobs
		 */
		switch (gspca_dev->usb_buf[0]) {
		case 2:
			sd->sensor_type = 0;
			break;
		case 3:
			sd->sensor_type = 1;
			break;
		default:
			pr_err("Unknown CIF Sensor id : %02x\n",
			       gspca_dev->usb_buf[1]);
			return -ENODEV;
		}
		gspca_dbg(gspca_dev, D_PROBE, "MR97310A CIF camera detected, sensor: %d\n",
			  sd->sensor_type);
	} else {
		sd->cam_type = CAM_TYPE_VGA;

		/*
		 * Here is a table of the responses to the query for sensor
		 * type, from the known MR97310A VGA cameras. Six different
		 * cameras of which five share the same USB ID.
		 *
		 * Name			gspca_dev->usb_buf[]	sd->sensor_type
		 *				sd->do_lcd_stop
		 * Aiptek Pencam VGA+	0300		0		1
		 * ION digital		0300		0		1
		 * Argus DC-1620	0450		1		0
		 * Argus QuickClix	0420		1		1
		 * Sakar 77379 Digital	0350		0		1
		 * Sakar 1638x CyberPix	0120		0		2
		 *
		 * Based upon these results, we assume default settings
		 * and then correct as necessary, as follows.
		 *
		 */

		sd->sensor_type = 1;
		sd->do_lcd_stop = 0;
		sd->adj_colors = 0;
		if (gspca_dev->usb_buf[0] == 0x01) {
			sd->sensor_type = 2;
		} else if ((gspca_dev->usb_buf[0] != 0x03) &&
					(gspca_dev->usb_buf[0] != 0x04)) {
			pr_err("Unknown VGA Sensor id Byte 0: %02x\n",
			       gspca_dev->usb_buf[0]);
			pr_err("Defaults assumed, may not work\n");
			pr_err("Please report this\n");
		}
		/* Sakar Digital color needs to be adjusted. */
		if ((gspca_dev->usb_buf[0] == 0x03) &&
					(gspca_dev->usb_buf[1] == 0x50))
			sd->adj_colors = 1;
		if (gspca_dev->usb_buf[0] == 0x04) {
			sd->do_lcd_stop = 1;
			switch (gspca_dev->usb_buf[1]) {
			case 0x50:
				sd->sensor_type = 0;
				gspca_dbg(gspca_dev, D_PROBE, "sensor_type corrected to 0\n");
				break;
			case 0x20:
				/* Nothing to do here. */
				break;
			default:
				pr_err("Unknown VGA Sensor id Byte 1: %02x\n",
				       gspca_dev->usb_buf[1]);
				pr_err("Defaults assumed, may not work\n");
				pr_err("Please report this\n");
			}
		}
		gspca_dbg(gspca_dev, D_PROBE, "MR97310A VGA camera detected, sensor: %d\n",
			  sd->sensor_type);
	}
	/* Stop streaming as we've started it only to probe the sensor type. */
	sd_stopN(gspca_dev);

	if (force_sensor_type != -1) {
		sd->sensor_type = !!force_sensor_type;
		gspca_dbg(gspca_dev, D_PROBE, "Forcing sensor type to: %d\n",
			  sd->sensor_type);
	}

	return 0;
}