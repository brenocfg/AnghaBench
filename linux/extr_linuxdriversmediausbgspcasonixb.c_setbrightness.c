#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sd {int sensor; TYPE_1__* brightness; } ;
struct gspca_dev {int dummy; } ;
typedef  int __u8 ;
struct TYPE_4__ {int sensor_addr; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
#define  SENSOR_OV6650 131 
#define  SENSOR_OV7630 130 
#define  SENSOR_PAS106 129 
#define  SENSOR_PAS202 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 TYPE_2__* sensor_data ; 

__attribute__((used)) static void setbrightness(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	switch (sd->sensor) {
	case  SENSOR_OV6650:
	case  SENSOR_OV7630: {
		__u8 i2cOV[] =
			{0xa0, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x10};

		/* change reg 0x06 */
		i2cOV[1] = sensor_data[sd->sensor].sensor_addr;
		i2cOV[3] = sd->brightness->val;
		i2c_w(gspca_dev, i2cOV);
		break;
	}
	case SENSOR_PAS106:
	case SENSOR_PAS202: {
		__u8 i2cpbright[] =
			{0xb0, 0x40, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x16};
		__u8 i2cpdoit[] =
			{0xa0, 0x40, 0x11, 0x01, 0x00, 0x00, 0x00, 0x16};

		/* PAS106 uses reg 7 and 8 instead of b and c */
		if (sd->sensor == SENSOR_PAS106) {
			i2cpbright[2] = 7;
			i2cpdoit[2] = 0x13;
		}

		if (sd->brightness->val < 127) {
			/* change reg 0x0b, signreg */
			i2cpbright[3] = 0x01;
			/* set reg 0x0c, offset */
			i2cpbright[4] = 127 - sd->brightness->val;
		} else
			i2cpbright[4] = sd->brightness->val - 127;

		i2c_w(gspca_dev, i2cpbright);
		i2c_w(gspca_dev, i2cpdoit);
		break;
	}
	default:
		break;
	}
}