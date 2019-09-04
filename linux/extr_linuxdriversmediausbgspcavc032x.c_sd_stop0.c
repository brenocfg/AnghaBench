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
struct sd {scalar_t__ sensor; int flags; } ;
struct gspca_dev {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int FL_SAMSUNG ; 
 scalar_t__ SENSOR_MI1310_SOC ; 
 scalar_t__ SENSOR_POxxxx ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void sd_stop0(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (!gspca_dev->present)
		return;
/*fixme: is this useful?*/
	if (sd->sensor == SENSOR_MI1310_SOC)
		reg_w(gspca_dev, 0x89, 0x058c, 0x00ff);
	else if (!(sd->flags & FL_SAMSUNG))
		reg_w(gspca_dev, 0x89, 0xffff, 0xffff);

	if (sd->sensor == SENSOR_POxxxx) {
		reg_w(gspca_dev, 0xa0, 0x26, 0xb300);
		reg_w(gspca_dev, 0xa0, 0x04, 0xb300);
		reg_w(gspca_dev, 0xa0, 0x00, 0xb300);
	}
}