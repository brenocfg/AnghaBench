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
struct sd {int /*<<< orphan*/  sharpness; int /*<<< orphan*/  gamma; } ;
struct gspca_dev {int alt; scalar_t__ curr_mode; } ;
struct cmd {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct cmd const*) ; 
#define  CX0342_ADCGN 152 
#define  CX0342_ADC_CTL 151 
#define  CX0342_AUTO_ADC_CALIB 150 
#define  CX0342_EXPO_LINE_H 149 
#define  CX0342_EXPO_LINE_L 148 
#define  CX0342_IDLE_CTRL 147 
#define  CX0342_LDOSEL 146 
#define  CX0342_LVRST_BLBIAS 145 
#define  CX0342_RAMP_RIV 144 
#define  CX0342_RAW_BGAIN_L 143 
#define  CX0342_RAW_GBGAIN_L 142 
#define  CX0342_RAW_GRGAIN_L 141 
#define  CX0342_RAW_RGAIN_L 140 
#define  CX0342_SPV_VALUE_H 139 
#define  CX0342_SPV_VALUE_L 138 
#define  CX0342_SYS_CTRL_0 137 
#define  CX0342_VTHSEL 136 
 size_t SENSOR_CX0342 ; 
#define  TP6800_R31_PIXEL_START 135 
#define  TP6800_R32_PIXEL_END_L 134 
#define  TP6800_R33_PIXEL_END_H 133 
#define  TP6800_R34_LINE_START 132 
#define  TP6800_R35_LINE_END_L 131 
#define  TP6800_R36_LINE_END_H 130 
 int TP6800_R3F_FRAME_RATE ; 
 int TP6800_R78_FORMAT ; 
#define  TP6800_R79_QUALITY 129 
#define  TP6800_R7A_BLK_THRLD 128 
 int /*<<< orphan*/  bulk_w (struct gspca_dev*,int,struct cmd const*,int /*<<< orphan*/ ) ; 
 struct cmd const** color_gain ; 
 int /*<<< orphan*/  i2c_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  setgamma (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsharpness (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 struct cmd const* tp6810_bridge_start ; 
 struct cmd const* tp6810_cx_init_common ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx0342_6810_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const struct cmd sensor_init_2[] = {
		{CX0342_EXPO_LINE_L, 0x6f},
		{CX0342_EXPO_LINE_H, 0x02},
		{CX0342_RAW_GRGAIN_L, 0x00},
		{CX0342_RAW_GBGAIN_L, 0x00},
		{CX0342_RAW_RGAIN_L, 0x00},
		{CX0342_RAW_BGAIN_L, 0x00},
		{CX0342_SYS_CTRL_0, 0x81},
	};
	static const struct cmd bridge_init_2[] = {
		{0x4d, 0x00},
		{0x4c, 0xff},
		{0x4e, 0xff},
		{0x4f, 0x00},
		{TP6800_R7A_BLK_THRLD, 0x00},
		{TP6800_R79_QUALITY, 0x04},
		{TP6800_R79_QUALITY, 0x01},
	};
	static const struct cmd bridge_init_3[] = {
		{TP6800_R31_PIXEL_START, 0x08},
		{TP6800_R32_PIXEL_END_L, 0x87},
		{TP6800_R33_PIXEL_END_H, 0x02},
		{TP6800_R34_LINE_START, 0x0e},
		{TP6800_R35_LINE_END_L, 0xf4},
		{TP6800_R36_LINE_END_H, 0x01},
	};
	static const struct cmd sensor_init_3[] = {
		{CX0342_AUTO_ADC_CALIB, 0x81},
		{CX0342_EXPO_LINE_L, 0x6f},
		{CX0342_EXPO_LINE_H, 0x02},
		{CX0342_RAW_GRGAIN_L, 0x00},
		{CX0342_RAW_GBGAIN_L, 0x00},
		{CX0342_RAW_RGAIN_L, 0x00},
		{CX0342_RAW_BGAIN_L, 0x00},
		{CX0342_SYS_CTRL_0, 0x81},
	};
	static const struct cmd bridge_init_5[] = {
		{0x4d, 0x00},
		{0x4c, 0xff},
		{0x4e, 0xff},
		{0x4f, 0x00},
	};
	static const struct cmd sensor_init_4[] = {
		{CX0342_EXPO_LINE_L, 0xd3},
		{CX0342_EXPO_LINE_H, 0x01},
/*fixme: gains, but 00..80 only*/
		{CX0342_RAW_GRGAIN_L, 0x40},
		{CX0342_RAW_GBGAIN_L, 0x40},
		{CX0342_RAW_RGAIN_L, 0x40},
		{CX0342_RAW_BGAIN_L, 0x40},
		{CX0342_SYS_CTRL_0, 0x81},
	};
	static const struct cmd sensor_init_5[] = {
		{CX0342_IDLE_CTRL, 0x05},
		{CX0342_ADCGN, 0x00},
		{CX0342_ADC_CTL, 0x00},
		{CX0342_LVRST_BLBIAS, 0x01},
		{CX0342_VTHSEL, 0x0b},
		{CX0342_RAMP_RIV, 0x0b},
		{CX0342_LDOSEL, 0x07},
		{CX0342_SPV_VALUE_L, 0x40},
		{CX0342_SPV_VALUE_H, 0x02},
		{CX0342_AUTO_ADC_CALIB, 0x81},
	};

	reg_w(gspca_dev, 0x22, gspca_dev->alt);
	i2c_w_buf(gspca_dev, sensor_init_2, ARRAY_SIZE(sensor_init_2));
	reg_w_buf(gspca_dev, bridge_init_2, ARRAY_SIZE(bridge_init_2));
	reg_w_buf(gspca_dev, tp6810_cx_init_common,
			ARRAY_SIZE(tp6810_cx_init_common));
	reg_w_buf(gspca_dev, bridge_init_3, ARRAY_SIZE(bridge_init_3));
	if (gspca_dev->curr_mode) {
		reg_w(gspca_dev, 0x4a, 0x7f);
		reg_w(gspca_dev, 0x07, 0x05);
		reg_w(gspca_dev, TP6800_R78_FORMAT, 0x00);	/* vga */
	} else {
		reg_w(gspca_dev, 0x4a, 0xff);
		reg_w(gspca_dev, 0x07, 0x85);
		reg_w(gspca_dev, TP6800_R78_FORMAT, 0x01);	/* qvga */
	}
	setgamma(gspca_dev, v4l2_ctrl_g_ctrl(sd->gamma));
	reg_w_buf(gspca_dev, tp6810_bridge_start,
			ARRAY_SIZE(tp6810_bridge_start));
	setsharpness(gspca_dev, v4l2_ctrl_g_ctrl(sd->sharpness));
	bulk_w(gspca_dev, 0x03, color_gain[SENSOR_CX0342],
				ARRAY_SIZE(color_gain[0]));
	reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, 0x87);
	i2c_w_buf(gspca_dev, sensor_init_3, ARRAY_SIZE(sensor_init_3));
	reg_w_buf(gspca_dev, bridge_init_5, ARRAY_SIZE(bridge_init_5));
	i2c_w_buf(gspca_dev, sensor_init_4, ARRAY_SIZE(sensor_init_4));
	reg_w_buf(gspca_dev, bridge_init_5, ARRAY_SIZE(bridge_init_5));
	i2c_w_buf(gspca_dev, sensor_init_5, ARRAY_SIZE(sensor_init_5));

	set_led(gspca_dev, 1);
/*	setquality(gspca_dev, v4l2_ctrl_g_ctrl(sd->jpegqual)); */
}