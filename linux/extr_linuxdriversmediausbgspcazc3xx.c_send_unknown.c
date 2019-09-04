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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
#define  SENSOR_ADCM2700 137 
#define  SENSOR_GC0305 136 
#define  SENSOR_HV7131R 135 
#define  SENSOR_MT9V111_1 134 
#define  SENSOR_MT9V111_3 133 
#define  SENSOR_OV7620 132 
#define  SENSOR_PAS106 131 
#define  SENSOR_PAS202B 130 
#define  SENSOR_PB0330 129 
#define  SENSOR_PO2030 128 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void send_unknown(struct gspca_dev *gspca_dev, int sensor)
{
	reg_w(gspca_dev, 0x01, 0x0000);		/* bridge reset */
	switch (sensor) {
	case SENSOR_PAS106:
		reg_w(gspca_dev, 0x03, 0x003a);
		reg_w(gspca_dev, 0x0c, 0x003b);
		reg_w(gspca_dev, 0x08, 0x0038);
		break;
	case SENSOR_ADCM2700:
	case SENSOR_GC0305:
	case SENSOR_OV7620:
	case SENSOR_MT9V111_1:
	case SENSOR_MT9V111_3:
	case SENSOR_PB0330:
	case SENSOR_PO2030:
		reg_w(gspca_dev, 0x0d, 0x003a);
		reg_w(gspca_dev, 0x02, 0x003b);
		reg_w(gspca_dev, 0x00, 0x0038);
		break;
	case SENSOR_HV7131R:
	case SENSOR_PAS202B:
		reg_w(gspca_dev, 0x03, 0x003b);
		reg_w(gspca_dev, 0x0c, 0x003a);
		reg_w(gspca_dev, 0x0b, 0x0039);
		if (sensor == SENSOR_PAS202B)
			reg_w(gspca_dev, 0x0b, 0x0038);
		break;
	}
}