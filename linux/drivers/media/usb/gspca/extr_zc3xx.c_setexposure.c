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
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case SENSOR_HV7131R:
		i2c_write(gspca_dev, 0x25, val >> 9, 0x00);
		i2c_write(gspca_dev, 0x26, val >> 1, 0x00);
		i2c_write(gspca_dev, 0x27, val << 7, 0x00);
		break;
	case SENSOR_OV7620:
		i2c_write(gspca_dev, 0x10, val, 0x00);
		break;
	}
}