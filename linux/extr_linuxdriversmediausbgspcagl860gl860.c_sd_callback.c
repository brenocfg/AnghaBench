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
struct sd {int nbRightUp; int mirrorMask; int waitSet; int /*<<< orphan*/  (* dev_camera_settings ) (struct gspca_dev*) ;} ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _OV9655_ ; 
 int /*<<< orphan*/  ctrl_in (struct gspca_dev*,int,int,int,int,int,void*) ; 
 int /*<<< orphan*/  stub1 (struct gspca_dev*) ; 

__attribute__((used)) static void sd_callback(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!_OV9655_) {
		u8 state;
		u8 upsideDown;

		/* Probe sensor orientation */
		ctrl_in(gspca_dev, 0xc0, 2, 0x0000, 0x0000, 1, (void *)&state);

		/* C8/40 means upside-down (looking backwards) */
		/* D8/50 means right-up (looking onwards) */
		upsideDown = (state == 0xc8 || state == 0x40);

		if (upsideDown && sd->nbRightUp > -4) {
			if (sd->nbRightUp > 0)
				sd->nbRightUp = 0;
			if (sd->nbRightUp == -3) {
				sd->mirrorMask = 1;
				sd->waitSet = 1;
			}
			sd->nbRightUp--;
		}
		if (!upsideDown && sd->nbRightUp < 4) {
			if (sd->nbRightUp  < 0)
				sd->nbRightUp = 0;
			if (sd->nbRightUp == 3) {
				sd->mirrorMask = 0;
				sd->waitSet = 1;
			}
			sd->nbRightUp++;
		}
	}

	if (sd->waitSet)
		sd->dev_camera_settings(gspca_dev);
}