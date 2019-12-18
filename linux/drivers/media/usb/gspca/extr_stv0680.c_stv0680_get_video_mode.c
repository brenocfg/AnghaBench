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
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int stv0680_handle_error (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int stv_sndctrl (struct gspca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stv0680_get_video_mode(struct gspca_dev *gspca_dev)
{
	/* Note not sure if this init of usb_buf is really necessary */
	memset(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = 0x0f;

	if (stv_sndctrl(gspca_dev, 0, 0x87, 0, 0x08) != 0x08) {
		gspca_err(gspca_dev, "Get_Camera_Mode failed\n");
		return stv0680_handle_error(gspca_dev, -EIO);
	}

	return gspca_dev->usb_buf[0]; /* 01 = VGA, 03 = QVGA, 00 = CIF */
}