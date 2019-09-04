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
struct sd {int* firmware_id; int block_size; int /*<<< orphan*/  work_struct; } ;
struct cam {int bulk_size; int bulk; void* nmodes; void* cam_mode; } ;
struct gspca_dev {struct cam cam; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* cif_mode ; 
 int /*<<< orphan*/  jl2005c_dostream ; 
 int /*<<< orphan*/  jl2005c_get_firmware_id (struct gspca_dev*) ; 
 void* vga_mode ; 

__attribute__((used)) static int sd_config(struct gspca_dev *gspca_dev,
			const struct usb_device_id *id)
{
	struct cam *cam;
	struct sd *sd = (struct sd *) gspca_dev;

	cam = &gspca_dev->cam;
	/* We don't use the buffer gspca allocates so make it small. */
	cam->bulk_size = 64;
	cam->bulk = 1;
	/* For the rest, the camera needs to be detected */
	jl2005c_get_firmware_id(gspca_dev);
	/* Here are some known firmware IDs
	 * First some JL2005B cameras
	 * {0x41, 0x07, 0x04, 0x2c, 0xe8, 0xf2}	Sakar KidzCam
	 * {0x45, 0x02, 0x08, 0xb9, 0x00, 0xd2}	No-name JL2005B
	 * JL2005C cameras
	 * {0x01, 0x0c, 0x16, 0x10, 0xf8, 0xc8}	Argus DC-1512
	 * {0x12, 0x04, 0x03, 0xc0, 0x00, 0xd8}	ICarly
	 * {0x86, 0x08, 0x05, 0x02, 0x00, 0xd4}	Jazz
	 *
	 * Based upon this scanty evidence, we can detect a CIF camera by
	 * testing byte 0 for 0x4x.
	 */
	if ((sd->firmware_id[0] & 0xf0) == 0x40) {
		cam->cam_mode	= cif_mode;
		cam->nmodes	= ARRAY_SIZE(cif_mode);
		sd->block_size	= 0x80;
	} else {
		cam->cam_mode	= vga_mode;
		cam->nmodes	= ARRAY_SIZE(vga_mode);
		sd->block_size	= 0x200;
	}

	INIT_WORK(&sd->work_struct, jl2005c_dostream);

	return 0;
}