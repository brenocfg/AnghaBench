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
struct sd {int sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  SENSOR_PO1200 129 
#define  SENSOR_POxxxx 128 
 int /*<<< orphan*/  i2c_write (struct gspca_dev*,int,int*,int) ; 

__attribute__((used)) static void setsharpness(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 data;

	switch (sd->sensor) {
	case SENSOR_PO1200:
		data = 0;
		i2c_write(gspca_dev, 0x03, &data, 1);
		if (val < 0)
			data = 0x6a;
		else
			data = 0xb5 + val * 3;
		i2c_write(gspca_dev, 0x61, &data, 1);
		break;
	case SENSOR_POxxxx:
		if (val < 0)
			data = 0x7e;	/* def = max */
		else
			data = 0x60 + val * 0x0f;
		i2c_write(gspca_dev, 0x59, &data, 1);
		break;
	}
}