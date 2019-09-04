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
struct sd {scalar_t__ ag_cnt; scalar_t__ bridge; int ae_res; int webcam; } ;
struct gspca_dev {int* usb_buf; } ;

/* Variables and functions */
 scalar_t__ AG_CNT_START ; 
 scalar_t__ BRIDGE_NW801 ; 
#define  P35u 128 
 int /*<<< orphan*/  gspca_coarse_grained_expo_autogain (struct gspca_dev*,int,int,int) ; 
 int /*<<< orphan*/  gspca_expo_autogain (struct gspca_dev*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void do_autogain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int luma;

	if (sd->ag_cnt < 0)
		return;
	if (--sd->ag_cnt >= 0)
		return;
	sd->ag_cnt = AG_CNT_START;

	/* get the average luma */
	reg_r(gspca_dev, sd->bridge == BRIDGE_NW801 ? 0x080d : 0x080c, 4);
	luma = (gspca_dev->usb_buf[3] << 24) + (gspca_dev->usb_buf[2] << 16)
		+ (gspca_dev->usb_buf[1] << 8) + gspca_dev->usb_buf[0];
	luma /= sd->ae_res;

	switch (sd->webcam) {
	case P35u:
		gspca_coarse_grained_expo_autogain(gspca_dev, luma, 100, 5);
		break;
	default:
		gspca_expo_autogain(gspca_dev, luma, 100, 5, 230, 0);
		break;
	}
}