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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV767x ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setlightfreq(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	val = val ? 0x9e : 0x00;
	if (sd->sensor == SENSOR_OV767x) {
		sccb_reg_write(gspca_dev, 0x2a, 0x00);
		if (val)
			val = 0x9d;	/* insert dummy to 25fps for 50Hz */
	}
	sccb_reg_write(gspca_dev, 0x2b, val);
}