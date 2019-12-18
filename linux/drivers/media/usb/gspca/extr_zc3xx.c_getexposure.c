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
struct sd {int sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  SENSOR_HV7131R 129 
#define  SENSOR_OV7620 128 
 int i2c_read (struct gspca_dev*,int) ; 

__attribute__((used)) static s32 getexposure(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_HV7131R:
		return (i2c_read(gspca_dev, 0x25) << 9)
			| (i2c_read(gspca_dev, 0x26) << 1)
			| (i2c_read(gspca_dev, 0x27) >> 7);
	case SENSOR_OV7620:
		return i2c_read(gspca_dev, 0x10);
	default:
		return -1;
	}
}