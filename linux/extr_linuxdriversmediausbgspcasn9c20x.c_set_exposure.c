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
typedef  int s32 ;

/* Variables and functions */
#define  SENSOR_HV7131R 135 
#define  SENSOR_MT9M001 134 
#define  SENSOR_MT9V011 133 
#define  SENSOR_MT9V112 132 
#define  SENSOR_OV7660 131 
#define  SENSOR_OV7670 130 
#define  SENSOR_OV9650 129 
#define  SENSOR_OV9655 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 

__attribute__((used)) static void set_exposure(struct gspca_dev *gspca_dev, s32 expo)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 exp[8] = {sd->i2c_intf, sd->i2c_addr,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x10};
	int expo2;

	if (gspca_dev->streaming)
		exp[7] = 0x1e;

	switch (sd->sensor) {
	case SENSOR_OV7660:
	case SENSOR_OV7670:
	case SENSOR_OV9655:
	case SENSOR_OV9650:
		if (expo > 547)
			expo2 = 547;
		else
			expo2 = expo;
		exp[0] |= (2 << 4);
		exp[2] = 0x10;			/* AECH */
		exp[3] = expo2 >> 2;
		exp[7] = 0x10;
		i2c_w(gspca_dev, exp);
		exp[2] = 0x04;			/* COM1 */
		exp[3] = expo2 & 0x0003;
		exp[7] = 0x10;
		i2c_w(gspca_dev, exp);
		expo -= expo2;
		exp[7] = 0x1e;
		exp[0] |= (3 << 4);
		exp[2] = 0x2d;			/* ADVFL & ADVFH */
		exp[3] = expo;
		exp[4] = expo >> 8;
		break;
	case SENSOR_MT9M001:
	case SENSOR_MT9V112:
	case SENSOR_MT9V011:
		exp[0] |= (3 << 4);
		exp[2] = 0x09;
		exp[3] = expo >> 8;
		exp[4] = expo;
		break;
	case SENSOR_HV7131R:
		exp[0] |= (4 << 4);
		exp[2] = 0x25;
		exp[3] = expo >> 5;
		exp[4] = expo << 3;
		exp[5] = 0;
		break;
	default:
		return;
	}
	i2c_w(gspca_dev, exp);
}