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
typedef  int u16 ;
struct sensor_s {int i2c_addr; int i2c_dum; } ;
struct sd {int sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  SENSOR_ICX098BQ 129 
#define  SENSOR_LZ24BP 128 
 int SQ930_CTRL_SET_EXPOSURE ; 
 int /*<<< orphan*/  reg_wb (struct gspca_dev*,int,int /*<<< orphan*/ ,int*,int) ; 
 struct sensor_s* sensor_tb ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 expo, s32 gain)
{
	struct sd *sd = (struct sd *) gspca_dev;
	int i, integclks, intstartclk, frameclks, min_frclk;
	const struct sensor_s *sensor;
	u16 cmd;
	u8 buf[15];

	integclks = expo;
	i = 0;
	cmd = SQ930_CTRL_SET_EXPOSURE;

	switch (sd->sensor) {
	case SENSOR_ICX098BQ:			/* ccd */
	case SENSOR_LZ24BP:
		min_frclk = sd->sensor == SENSOR_ICX098BQ ? 0x210 : 0x26f;
		if (integclks >= min_frclk) {
			intstartclk = 0;
			frameclks = integclks;
		} else {
			intstartclk = min_frclk - integclks;
			frameclks = min_frclk;
		}
		buf[i++] = intstartclk >> 8;
		buf[i++] = intstartclk;
		buf[i++] = frameclks >> 8;
		buf[i++] = frameclks;
		buf[i++] = gain;
		break;
	default:				/* cmos */
/*	case SENSOR_MI0360: */
/*	case SENSOR_MT9V111: */
		cmd |= 0x0100;
		sensor = &sensor_tb[sd->sensor];
		buf[i++] = sensor->i2c_addr;	/* i2c_slave_addr */
		buf[i++] = 0x08;	/* 2 * ni2c */
		buf[i++] = 0x09;	/* reg = shutter width */
		buf[i++] = integclks >> 8; /* val H */
		buf[i++] = sensor->i2c_dum;
		buf[i++] = integclks;	/* val L */
		buf[i++] = 0x35;	/* reg = global gain */
		buf[i++] = 0x00;	/* val H */
		buf[i++] = sensor->i2c_dum;
		buf[i++] = 0x80 + gain / 2; /* val L */
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x00;
		buf[i++] = 0x83;
		break;
	}
	reg_wb(gspca_dev, cmd, 0, buf, i);
}