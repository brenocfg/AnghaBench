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
struct sd {int i2c_addr; int flags; int sensor; } ;
struct gspca_dev {scalar_t__ usb_err; } ;

/* Variables and functions */
 int ARRAY_SIZE (int**) ; 
 scalar_t__ ENODEV ; 
 int LED_REVERSE ; 
#define  SENSOR_HV7131R 137 
#define  SENSOR_MT9M001 136 
#define  SENSOR_MT9M111 135 
#define  SENSOR_MT9M112 134 
#define  SENSOR_MT9VPRB 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_OV7670 131 
#define  SENSOR_OV9650 130 
#define  SENSOR_OV9655 129 
#define  SENSOR_SOI968 128 
 int** bridge_init ; 
 int /*<<< orphan*/  hv7131r_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9m001_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9m111_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9m112_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  mt9v_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov7660_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov7670_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov9650_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  ov9655_init_sensor (struct gspca_dev*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  soi968_init_sensor (struct gspca_dev*) ; 

__attribute__((used)) static int sd_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i;
	u8 value;
	u8 i2c_init[9] = {
		0x80, sd->i2c_addr, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03
	};

	for (i = 0; i < ARRAY_SIZE(bridge_init); i++) {
		value = bridge_init[i][1];
		reg_w(gspca_dev, bridge_init[i][0], &value, 1);
		if (gspca_dev->usb_err < 0) {
			pr_err("Device initialization failed\n");
			return gspca_dev->usb_err;
		}
	}

	if (sd->flags & LED_REVERSE)
		reg_w1(gspca_dev, 0x1006, 0x00);
	else
		reg_w1(gspca_dev, 0x1006, 0x20);

	reg_w(gspca_dev, 0x10c0, i2c_init, 9);
	if (gspca_dev->usb_err < 0) {
		pr_err("Device initialization failed\n");
		return gspca_dev->usb_err;
	}

	switch (sd->sensor) {
	case SENSOR_OV9650:
		ov9650_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("OV9650 sensor detected\n");
		break;
	case SENSOR_OV9655:
		ov9655_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("OV9655 sensor detected\n");
		break;
	case SENSOR_SOI968:
		soi968_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("SOI968 sensor detected\n");
		break;
	case SENSOR_OV7660:
		ov7660_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("OV7660 sensor detected\n");
		break;
	case SENSOR_OV7670:
		ov7670_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("OV7670 sensor detected\n");
		break;
	case SENSOR_MT9VPRB:
		mt9v_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("MT9VPRB sensor detected\n");
		break;
	case SENSOR_MT9M111:
		mt9m111_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("MT9M111 sensor detected\n");
		break;
	case SENSOR_MT9M112:
		mt9m112_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("MT9M112 sensor detected\n");
		break;
	case SENSOR_MT9M001:
		mt9m001_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		break;
	case SENSOR_HV7131R:
		hv7131r_init_sensor(gspca_dev);
		if (gspca_dev->usb_err < 0)
			break;
		pr_info("HV7131R sensor detected\n");
		break;
	default:
		pr_err("Unsupported sensor\n");
		gspca_dev->usb_err = -ENODEV;
	}
	return gspca_dev->usb_err;
}