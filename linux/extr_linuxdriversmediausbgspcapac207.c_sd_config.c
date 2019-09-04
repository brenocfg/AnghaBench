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
typedef  int u8 ;
struct usb_device_id {int idVendor; int idProduct; } ;
struct cam {int /*<<< orphan*/  nmodes; int /*<<< orphan*/  cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  D_PROBE ; 
 int ENODEV ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,...) ; 
 int pac207_read_reg (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sif_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct cam *cam;
	u8 idreg[2];

	idreg[0] = pac207_read_reg(gspca_dev, 0x0000);
	idreg[1] = pac207_read_reg(gspca_dev, 0x0001);
	idreg[0] = ((idreg[0] & 0x0f) << 4) | ((idreg[1] & 0xf0) >> 4);
	idreg[1] = idreg[1] & 0x0f;
	gspca_dbg(gspca_dev, D_PROBE, "Pixart Sensor ID 0x%02X Chips ID 0x%02X\n",
		  idreg[0], idreg[1]);

	if (idreg[0] != 0x27) {
		gspca_dbg(gspca_dev, D_PROBE, "Error invalid sensor ID!\n");
		return -ENODEV;
	}

	gspca_dbg(gspca_dev, D_PROBE,
		  "Pixart PAC207BCA Image Processor and Control Chip detected (vid/pid 0x%04X:0x%04X)\n",
		  id->idVendor, id->idProduct);

	cam = &gspca_dev->cam;
	cam->cam_mode = sif_mode;
	cam->nmodes = ARRAY_SIZE(sif_mode);

	return 0;
}