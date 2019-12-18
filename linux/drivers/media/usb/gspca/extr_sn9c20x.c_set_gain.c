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
struct sd {int i2c_intf; int i2c_addr; int sensor; } ;
struct gspca_dev {scalar_t__ streaming; } ;
typedef  size_t s32 ;

/* Variables and functions */
#define  SENSOR_HV7131R 136 
#define  SENSOR_MT9M001 135 
#define  SENSOR_MT9V011 134 
#define  SENSOR_MT9V112 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_OV7670 131 
#define  SENSOR_OV9650 130 
#define  SENSOR_OV9655 129 
#define  SENSOR_SOI968 128 
 int* hv7131r_gain ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 int* micron1_gain ; 
 int* micron2_gain ; 
 int* ov_gain ; 

__attribute__((used)) static void set_gain(struct gspca_dev *gspca_dev, s32 g)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 gain[8] = {sd->i2c_intf, sd->i2c_addr,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x10};

	if (gspca_dev->streaming)
		gain[7] = 0x15;		/* or 1d ? */

	switch (sd->sensor) {
	case SENSOR_OV7660:
	case SENSOR_OV7670:
	case SENSOR_SOI968:
	case SENSOR_OV9655:
	case SENSOR_OV9650:
		gain[0] |= (2 << 4);
		gain[3] = ov_gain[g];
		break;
	case SENSOR_MT9V011:
		gain[0] |= (3 << 4);
		gain[2] = 0x35;
		gain[3] = micron1_gain[g] >> 8;
		gain[4] = micron1_gain[g];
		break;
	case SENSOR_MT9V112:
		gain[0] |= (3 << 4);
		gain[2] = 0x2f;
		gain[3] = micron1_gain[g] >> 8;
		gain[4] = micron1_gain[g];
		break;
	case SENSOR_MT9M001:
		gain[0] |= (3 << 4);
		gain[2] = 0x2f;
		gain[3] = micron2_gain[g] >> 8;
		gain[4] = micron2_gain[g];
		break;
	case SENSOR_HV7131R:
		gain[0] |= (2 << 4);
		gain[2] = 0x30;
		gain[3] = hv7131r_gain[g];
		break;
	default:
		return;
	}
	i2c_w(gspca_dev, gain);
}