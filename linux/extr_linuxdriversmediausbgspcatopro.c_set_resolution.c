#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {scalar_t__ sensor; int /*<<< orphan*/  jpegqual; int /*<<< orphan*/  gamma; } ;
struct TYPE_2__ {int width; } ;
struct gspca_dev {TYPE_1__ pixfmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX0342_AUTO_ADC_CALIB ; 
 int /*<<< orphan*/  CX0342_EXPO_LINE_H ; 
 int /*<<< orphan*/  CX0342_EXPO_LINE_L ; 
 int /*<<< orphan*/  CX0342_SYS_CTRL_0 ; 
 size_t SENSOR_CX0342 ; 
 scalar_t__ SENSOR_SOI763A ; 
 int /*<<< orphan*/  TP6800_R21_ENDP_1_CTL ; 
 int /*<<< orphan*/  TP6800_R3F_FRAME_RATE ; 
 int /*<<< orphan*/  TP6800_R5D_DEMOSAIC_CFG ; 
 int /*<<< orphan*/  TP6800_R78_FORMAT ; 
 int /*<<< orphan*/  bulk_w (struct gspca_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * color_gain ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setgamma (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setquality (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_resolution(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;

	reg_w(gspca_dev, TP6800_R21_ENDP_1_CTL, 0x00);
	if (gspca_dev->pixfmt.width == 320) {
		reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, 0x06);
		msleep(100);
		i2c_w(gspca_dev, CX0342_AUTO_ADC_CALIB, 0x01);
		msleep(100);
		reg_w(gspca_dev, TP6800_R21_ENDP_1_CTL, 0x03);
		reg_w(gspca_dev, TP6800_R78_FORMAT, 0x01);	/* qvga */
		reg_w(gspca_dev, TP6800_R5D_DEMOSAIC_CFG, 0x0d);
		i2c_w(gspca_dev, CX0342_EXPO_LINE_L, 0x37);
		i2c_w(gspca_dev, CX0342_EXPO_LINE_H, 0x01);
	} else {
		reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, 0x05);
		msleep(100);
		i2c_w(gspca_dev, CX0342_AUTO_ADC_CALIB, 0x01);
		msleep(100);
		reg_w(gspca_dev, TP6800_R21_ENDP_1_CTL, 0x03);
		reg_w(gspca_dev, TP6800_R78_FORMAT, 0x00);	/* vga */
		reg_w(gspca_dev, TP6800_R5D_DEMOSAIC_CFG, 0x09);
		i2c_w(gspca_dev, CX0342_EXPO_LINE_L, 0xcf);
		i2c_w(gspca_dev, CX0342_EXPO_LINE_H, 0x00);
	}
	i2c_w(gspca_dev, CX0342_SYS_CTRL_0, 0x01);
	bulk_w(gspca_dev, 0x03, color_gain[SENSOR_CX0342],
				ARRAY_SIZE(color_gain[0]));
	setgamma(gspca_dev, v4l2_ctrl_g_ctrl(sd->gamma));
	if (sd->sensor == SENSOR_SOI763A)
		setquality(gspca_dev, v4l2_ctrl_g_ctrl(sd->jpegqual));
}