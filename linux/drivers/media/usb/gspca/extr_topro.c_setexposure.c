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
struct sd {scalar_t__ sensor; scalar_t__ bridge; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BRIDGE_TP6800 ; 
 int CX0342_EXPO_LINE_H ; 
 int CX0342_EXPO_LINE_L ; 
 int CX0342_RAW_BGAIN_H ; 
 int CX0342_RAW_BGAIN_L ; 
 int CX0342_RAW_GBGAIN_H ; 
 int CX0342_RAW_GBGAIN_L ; 
 int CX0342_RAW_GRGAIN_H ; 
 int CX0342_RAW_GRGAIN_L ; 
 int CX0342_RAW_RGAIN_H ; 
 int CX0342_RAW_RGAIN_L ; 
 int CX0342_SYS_CTRL_0 ; 
 scalar_t__ SENSOR_CX0342 ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setexposure(struct gspca_dev *gspca_dev, s32 expo, s32 gain,
							s32 blue, s32 red)
{
	struct sd *sd = (struct sd *) gspca_dev;

	if (sd->sensor == SENSOR_CX0342) {
		expo = (expo << 2) - 1;
		i2c_w(gspca_dev, CX0342_EXPO_LINE_L, expo);
		i2c_w(gspca_dev, CX0342_EXPO_LINE_H, expo >> 8);
		if (sd->bridge == BRIDGE_TP6800)
			i2c_w(gspca_dev, CX0342_RAW_GBGAIN_H,
						gain >> 8);
		i2c_w(gspca_dev, CX0342_RAW_GBGAIN_L, gain);
		if (sd->bridge == BRIDGE_TP6800)
			i2c_w(gspca_dev, CX0342_RAW_GRGAIN_H,
					gain >> 8);
		i2c_w(gspca_dev, CX0342_RAW_GRGAIN_L, gain);
		if (sd->sensor == SENSOR_CX0342) {
			if (sd->bridge == BRIDGE_TP6800)
				i2c_w(gspca_dev, CX0342_RAW_BGAIN_H,
						blue >> 8);
			i2c_w(gspca_dev, CX0342_RAW_BGAIN_L, blue);
			if (sd->bridge == BRIDGE_TP6800)
				i2c_w(gspca_dev, CX0342_RAW_RGAIN_H,
						red >> 8);
			i2c_w(gspca_dev, CX0342_RAW_RGAIN_L, red);
		}
		i2c_w(gspca_dev, CX0342_SYS_CTRL_0,
				sd->bridge == BRIDGE_TP6800 ? 0x80 : 0x81);
		return;
	}

	/* soi763a */
	i2c_w(gspca_dev, 0x10,		/* AEC_H (exposure time) */
			 expo);
/*	i2c_w(gspca_dev, 0x76, 0x02);	 * AEC_L ([1:0] */
	i2c_w(gspca_dev, 0x00,		/* gain */
			 gain);
}