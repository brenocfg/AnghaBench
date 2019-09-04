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
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV767x ; 
 int sccb_reg_read (struct gspca_dev*,int) ; 

__attribute__((used)) static s32 getexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_OV767x) {
		/* get only aec[9:2] */
		return sccb_reg_read(gspca_dev, 0x10);	/* aech */
	} else {
		u8 hi = sccb_reg_read(gspca_dev, 0x08);
		u8 lo = sccb_reg_read(gspca_dev, 0x10);
		return (hi << 8 | lo) >> 1;
	}
}