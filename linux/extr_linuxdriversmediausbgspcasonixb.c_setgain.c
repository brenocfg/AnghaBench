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
typedef  int u8 ;
struct sd {int sensor; int /*<<< orphan*/  bridge; } ;
struct gspca_dev {TYPE_1__* gain; } ;
typedef  int __u8 ;
struct TYPE_4__ {int sensor_addr; } ;
struct TYPE_3__ {int val; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_103 ; 
#define  SENSOR_HV7131D 135 
#define  SENSOR_OV6650 134 
#define  SENSOR_OV7630 133 
#define  SENSOR_PAS106 132 
#define  SENSOR_PAS202 131 
#define  SENSOR_TAS5110C 130 
#define  SENSOR_TAS5110D 129 
#define  SENSOR_TAS5130CXX 128 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int*) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int*,int) ; 
 TYPE_2__* sensor_data ; 

__attribute__((used)) static void setgain(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 gain = gspca_dev->gain->val;

	switch (sd->sensor) {
	case SENSOR_HV7131D: {
		__u8 i2c[] =
			{0xc0, 0x11, 0x31, 0x00, 0x00, 0x00, 0x00, 0x17};

		i2c[3] = 0x3f - gain;
		i2c[4] = 0x3f - gain;
		i2c[5] = 0x3f - gain;

		i2c_w(gspca_dev, i2c);
		break;
	}
	case SENSOR_TAS5110C:
	case SENSOR_TAS5130CXX: {
		__u8 i2c[] =
			{0x30, 0x11, 0x02, 0x20, 0x70, 0x00, 0x00, 0x10};

		i2c[4] = 255 - gain;
		i2c_w(gspca_dev, i2c);
		break;
	}
	case SENSOR_TAS5110D: {
		__u8 i2c[] = {
			0xb0, 0x61, 0x02, 0x00, 0x10, 0x00, 0x00, 0x17 };
		gain = 255 - gain;
		/* The bits in the register are the wrong way around!! */
		i2c[3] |= (gain & 0x80) >> 7;
		i2c[3] |= (gain & 0x40) >> 5;
		i2c[3] |= (gain & 0x20) >> 3;
		i2c[3] |= (gain & 0x10) >> 1;
		i2c[3] |= (gain & 0x08) << 1;
		i2c[3] |= (gain & 0x04) << 3;
		i2c[3] |= (gain & 0x02) << 5;
		i2c[3] |= (gain & 0x01) << 7;
		i2c_w(gspca_dev, i2c);
		break;
	}
	case SENSOR_OV6650:
	case SENSOR_OV7630: {
		__u8 i2c[] = {0xa0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10};

		/*
		 * The ov7630's gain is weird, at 32 the gain drops to the
		 * same level as at 16, so skip 32-47 (of the 0-63 scale).
		 */
		if (sd->sensor == SENSOR_OV7630 && gain >= 32)
			gain += 16;

		i2c[1] = sensor_data[sd->sensor].sensor_addr;
		i2c[3] = gain;
		i2c_w(gspca_dev, i2c);
		break;
	}
	case SENSOR_PAS106:
	case SENSOR_PAS202: {
		__u8 i2cpgain[] =
			{0xa0, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x15};
		__u8 i2cpcolorgain[] =
			{0xc0, 0x40, 0x07, 0x00, 0x00, 0x00, 0x00, 0x15};
		__u8 i2cpdoit[] =
			{0xa0, 0x40, 0x11, 0x01, 0x00, 0x00, 0x00, 0x16};

		/* PAS106 uses different regs (and has split green gains) */
		if (sd->sensor == SENSOR_PAS106) {
			i2cpgain[2] = 0x0e;
			i2cpcolorgain[0] = 0xd0;
			i2cpcolorgain[2] = 0x09;
			i2cpdoit[2] = 0x13;
		}

		i2cpgain[3] = gain;
		i2cpcolorgain[3] = gain >> 1;
		i2cpcolorgain[4] = gain >> 1;
		i2cpcolorgain[5] = gain >> 1;
		i2cpcolorgain[6] = gain >> 1;

		i2c_w(gspca_dev, i2cpgain);
		i2c_w(gspca_dev, i2cpcolorgain);
		i2c_w(gspca_dev, i2cpdoit);
		break;
	}
	default:
		if (sd->bridge == BRIDGE_103) {
			u8 buf[3] = { gain, gain, gain }; /* R, G, B */
			reg_w(gspca_dev, 0x05, buf, 3);
		} else {
			u8 buf[2];
			buf[0] = gain << 4 | gain; /* Red and blue */
			buf[1] = gain; /* Green */
			reg_w(gspca_dev, 0x10, buf, 2);
		}
	}
}