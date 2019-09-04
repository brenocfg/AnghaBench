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
struct usb_device_id {int idProduct; int /*<<< orphan*/  idVendor; } ;
struct sd {int model; } ;
struct cam {int input_flags; void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int V4L2_IN_ST_HFLIP ; 
 int V4L2_IN_ST_VFLIP ; 
 void* cif_mode ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
		     const struct usb_device_id *id)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam *cam = &gspca_dev->cam;

	gspca_dbg(gspca_dev, D_PROBE, "SN9C2028 camera detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVendor, id->idProduct);

	sd->model = id->idProduct;

	switch (sd->model) {
	case 0x7005:
		gspca_dbg(gspca_dev, D_PROBE, "Genius Smart 300 camera\n");
		break;
	case 0x7003:
		gspca_dbg(gspca_dev, D_PROBE, "Genius Videocam Live v2\n");
		break;
	case 0x8000:
		gspca_dbg(gspca_dev, D_PROBE, "DC31VC\n");
		break;
	case 0x8001:
		gspca_dbg(gspca_dev, D_PROBE, "Spy camera\n");
		break;
	case 0x8003:
		gspca_dbg(gspca_dev, D_PROBE, "CIF camera\n");
		break;
	case 0x8008:
		gspca_dbg(gspca_dev, D_PROBE, "Mini-Shotz ms-350 camera\n");
		break;
	case 0x800a:
		gspca_dbg(gspca_dev, D_PROBE, "Vivitar 3350b type camera\n");
		cam->input_flags = V4L2_IN_ST_VFLIP | V4L2_IN_ST_HFLIP;
		break;
	}

	switch (sd->model) {
	case 0x8000:
	case 0x8001:
	case 0x8003:
		cam->cam_mode = cif_mode;
		cam->nmodes = ARRAY_SIZE(cif_mode);
		break;
	default:
		cam->cam_mode = vga_mode;
		cam->nmodes = ARRAY_SIZE(vga_mode);
	}
	return 0;
}