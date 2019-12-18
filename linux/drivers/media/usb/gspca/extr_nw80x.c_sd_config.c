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
struct usb_device_id {int idVendor; int idProduct; } ;
struct sd {int webcam; int ag_cnt; scalar_t__ bridge; } ;
struct TYPE_2__ {int needs_full_bandwidth; int nmodes; int /*<<< orphan*/ * cam_mode; } ;
struct gspca_dev {int* usb_buf; int usb_err; TYPE_1__ cam; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BRIDGE_NW800 ; 
 scalar_t__ BRIDGE_NW801 ; 
 scalar_t__ BRIDGE_NW802 ; 
#define  DS3303u 131 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int Generic800 ; 
 int Generic802 ; 
#define  Kr651us 130 
 unsigned int NWEBCAMS ; 
#define  P35u 129 
#define  Proscope 128 
 int SpaceCam ; 
 int SpaceCam2 ; 
 int Twinkle ; 
 int /*<<< orphan*/ * cif_mode ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  nw802_test_reg (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/ * vga_mode ; 
 int webcam ; 
 scalar_t__* webcam_chip ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if ((unsigned) webcam >= NWEBCAMS)
		webcam = 0;
	sd->webcam = webcam;
	gspca_dev->cam.needs_full_bandwidth = 1;
	sd->ag_cnt = -1;

	/*
	 * Autodetect sequence inspired from some log.
	 * We try to detect what registers exist or not.
	 * If 0x0500 does not exist => NW802
	 * If it does, test 0x109b. If it doesn't exist,
	 * then it's a NW801. Else, a NW800
	 * If a et31x110 (nw800 and 06a5:d800)
	 *	get the sensor ID
	 */
	if (!nw802_test_reg(gspca_dev, 0x0500, 0x55)) {
		sd->bridge = BRIDGE_NW802;
		if (sd->webcam == Generic800)
			sd->webcam = Generic802;
	} else if (!nw802_test_reg(gspca_dev, 0x109b, 0xaa)) {
		sd->bridge = BRIDGE_NW801;
		if (sd->webcam == Generic800)
			sd->webcam = P35u;
	} else if (id->idVendor == 0x06a5 && id->idProduct == 0xd800) {
		reg_r(gspca_dev, 0x0403, 1);		/* GPIO */
		gspca_dbg(gspca_dev, D_PROBE, "et31x110 sensor type %02x\n",
			  gspca_dev->usb_buf[0]);
		switch (gspca_dev->usb_buf[0] >> 1) {
		case 0x00:				/* ?? */
			if (sd->webcam == Generic800)
				sd->webcam = SpaceCam;
			break;
		case 0x01:				/* Hynix? */
			if (sd->webcam == Generic800)
				sd->webcam = Twinkle;
			break;
		case 0x0a:				/* Pixart */
			if (sd->webcam == Generic800)
				sd->webcam = SpaceCam2;
			break;
		}
	}
	if (webcam_chip[sd->webcam] != sd->bridge) {
		pr_err("Bad webcam type %d for NW80%d\n",
		       sd->webcam, sd->bridge);
		gspca_dev->usb_err = -ENODEV;
		return gspca_dev->usb_err;
	}
	gspca_dbg(gspca_dev, D_PROBE, "Bridge nw80%d - type: %d\n",
		  sd->bridge, sd->webcam);

	if (sd->bridge == BRIDGE_NW800) {
		switch (sd->webcam) {
		case DS3303u:
			gspca_dev->cam.cam_mode = cif_mode;	/* qvga */
			break;
		default:
			gspca_dev->cam.cam_mode = &cif_mode[1];	/* cif */
			break;
		}
		gspca_dev->cam.nmodes = 1;
	} else {
		gspca_dev->cam.cam_mode = vga_mode;
		switch (sd->webcam) {
		case Kr651us:
		case Proscope:
		case P35u:
			gspca_dev->cam.nmodes = ARRAY_SIZE(vga_mode);
			break;
		default:
			gspca_dev->cam.nmodes = 1;	/* qvga only */
			break;
		}
	}

	return gspca_dev->usb_err;
}