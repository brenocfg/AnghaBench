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
struct sd {int reg01; int reg17; int sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int LED ; 
 int SCL_SEL_OD ; 
#define  SENSOR_ADCM1700 141 
#define  SENSOR_GC0307 140 
#define  SENSOR_HV7131R 139 
#define  SENSOR_MI0360 138 
#define  SENSOR_MI0360B 137 
#define  SENSOR_MT9V111 136 
#define  SENSOR_OM6802 135 
#define  SENSOR_OV7630 134 
#define  SENSOR_OV7648 133 
#define  SENSOR_OV7660 132 
#define  SENSOR_PO1030 131 
#define  SENSOR_PO2030N 130 
#define  SENSOR_SOI768 129 
#define  SENSOR_SP80708 128 
 int SEN_CLK_EN ; 
 int SYS_SEL_48M ; 
 int S_PWR_DN ; 
 int V_TX_EN ; 
 int /*<<< orphan*/  i2c_w8 (struct gspca_dev*,int const*) ; 
 int /*<<< orphan*/  reg_w1 (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sd_stopN(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const u8 stophv7131[] =
		{ 0xa1, 0x11, 0x02, 0x09, 0x00, 0x00, 0x00, 0x10 };
	static const u8 stopmi0360[] =
		{ 0xb1, 0x5d, 0x07, 0x00, 0x00, 0x00, 0x00, 0x10 };
	static const u8 stopov7648[] =
		{ 0xa1, 0x21, 0x76, 0x20, 0x00, 0x00, 0x00, 0x10 };
	static const u8 stopsoi768[] =
		{ 0xa1, 0x21, 0x12, 0x80, 0x00, 0x00, 0x00, 0x10 };
	u8 reg01;
	u8 reg17;

	reg01 = sd->reg01;
	reg17 = sd->reg17 & ~SEN_CLK_EN;
	switch (sd->sensor) {
	case SENSOR_ADCM1700:
	case SENSOR_GC0307:
	case SENSOR_PO2030N:
	case SENSOR_SP80708:
		reg01 |= LED;
		reg_w1(gspca_dev, 0x01, reg01);
		reg01 &= ~(LED | V_TX_EN);
		reg_w1(gspca_dev, 0x01, reg01);
/*		reg_w1(gspca_dev, 0x02, 0x??);	 * LED off ? */
		break;
	case SENSOR_HV7131R:
		reg01 &= ~V_TX_EN;
		reg_w1(gspca_dev, 0x01, reg01);
		i2c_w8(gspca_dev, stophv7131);
		break;
	case SENSOR_MI0360:
	case SENSOR_MI0360B:
		reg01 &= ~V_TX_EN;
		reg_w1(gspca_dev, 0x01, reg01);
/*		reg_w1(gspca_dev, 0x02, 0x40);	  * LED off ? */
		i2c_w8(gspca_dev, stopmi0360);
		break;
	case SENSOR_MT9V111:
	case SENSOR_OM6802:
	case SENSOR_PO1030:
		reg01 &= ~V_TX_EN;
		reg_w1(gspca_dev, 0x01, reg01);
		break;
	case SENSOR_OV7630:
	case SENSOR_OV7648:
		reg01 &= ~V_TX_EN;
		reg_w1(gspca_dev, 0x01, reg01);
		i2c_w8(gspca_dev, stopov7648);
		break;
	case SENSOR_OV7660:
		reg01 &= ~V_TX_EN;
		reg_w1(gspca_dev, 0x01, reg01);
		break;
	case SENSOR_SOI768:
		i2c_w8(gspca_dev, stopsoi768);
		break;
	}

	reg01 |= SCL_SEL_OD;
	reg_w1(gspca_dev, 0x01, reg01);
	reg01 |= S_PWR_DN;		/* sensor power down */
	reg_w1(gspca_dev, 0x01, reg01);
	reg_w1(gspca_dev, 0x17, reg17);
	reg01 &= ~SYS_SEL_48M;		/* clock 24MHz */
	reg_w1(gspca_dev, 0x01, reg01);
	reg01 |= LED;
	reg_w1(gspca_dev, 0x01, reg01);
	/* Don't disable sensor clock as that disables the button on the cam */
	/* reg_w1(gspca_dev, 0xf1, 0x01); */
}