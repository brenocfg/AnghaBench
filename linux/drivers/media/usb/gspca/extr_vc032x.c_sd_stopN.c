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
struct sd {int sensor; int flags; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int FL_SAMSUNG ; 
#define  SENSOR_MI1310_SOC 129 
#define  SENSOR_POxxxx 128 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_MI1310_SOC:
		reg_w(gspca_dev, 0x89, 0x058c, 0x00ff);
		break;
	case SENSOR_POxxxx:
		return;
	default:
		if (!(sd->flags & FL_SAMSUNG))
			reg_w(gspca_dev, 0x89, 0xffff, 0xffff);
		break;
	}
	reg_w(gspca_dev, 0xa0, 0x01, 0xb301);
	reg_w(gspca_dev, 0xa0, 0x09, 0xb003);
}