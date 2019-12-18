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
struct sd {int ag_cnt; int ae_res; } ;
struct TYPE_2__ {int width; int height; } ;
struct gspca_dev {int* usb_buf; TYPE_1__ pixfmt; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int AG_CNT_START ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setautogain(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int w, h;

	if (!val) {
		sd->ag_cnt = -1;
		return;
	}
	sd->ag_cnt = AG_CNT_START;

	reg_r(gspca_dev, 0x1004, 1);
	if (gspca_dev->usb_buf[0] & 0x04) {	/* if AE_FULL_FRM */
		sd->ae_res = gspca_dev->pixfmt.width * gspca_dev->pixfmt.height;
	} else {				/* get the AE window size */
		reg_r(gspca_dev, 0x1011, 8);
		w = (gspca_dev->usb_buf[1] << 8) + gspca_dev->usb_buf[0]
		  - (gspca_dev->usb_buf[3] << 8) - gspca_dev->usb_buf[2];
		h = (gspca_dev->usb_buf[5] << 8) + gspca_dev->usb_buf[4]
		  - (gspca_dev->usb_buf[7] << 8) - gspca_dev->usb_buf[6];
		sd->ae_res = h * w;
		if (sd->ae_res == 0)
			sd->ae_res = gspca_dev->pixfmt.width *
					gspca_dev->pixfmt.height;
	}
}