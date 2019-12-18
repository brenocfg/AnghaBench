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
typedef  scalar_t__ u8 ;
struct sd {scalar_t__ current_mode; } ;
struct gspca_dev {scalar_t__* usb_buf; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stv0680_get_video_mode (struct gspca_dev*) ; 
 int stv0680_handle_error (struct gspca_dev*,int) ; 
 int stv_sndctrl (struct gspca_dev*,int,int,int,int) ; 

__attribute__((used)) static int stv0680_set_video_mode(struct gspca_dev *gspca_dev, u8 mode)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->current_mode == mode)
		return 0;

	memset(gspca_dev->usb_buf, 0, 8);
	gspca_dev->usb_buf[0] = mode;

	if (stv_sndctrl(gspca_dev, 3, 0x07, 0x0100, 0x08) != 0x08) {
		gspca_err(gspca_dev, "Set_Camera_Mode failed\n");
		return stv0680_handle_error(gspca_dev, -EIO);
	}

	/* Verify we got what we've asked for */
	if (stv0680_get_video_mode(gspca_dev) != mode) {
		gspca_err(gspca_dev, "Error setting camera video mode!\n");
		return -EIO;
	}

	sd->current_mode = mode;

	return 0;
}