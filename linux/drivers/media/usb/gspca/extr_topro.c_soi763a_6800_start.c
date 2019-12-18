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
struct sd {size_t sensor; int /*<<< orphan*/  gamma; int /*<<< orphan*/  jpegqual; int /*<<< orphan*/  red; int /*<<< orphan*/  blue; int /*<<< orphan*/  sharpness; } ;
struct gspca_dev {int /*<<< orphan*/  gain; int /*<<< orphan*/  exposure; } ;
struct cmd {int const member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct cmd const*) ; 
 size_t SENSOR_CX0342 ; 
 size_t SENSOR_SOI763A ; 
#define  TP6800_R10_SIF_TYPE 158 
#define  TP6800_R12_SIF_ADDR_S 157 
#define  TP6800_R1A_SIF_TX_DATA2 156 
#define  TP6800_R21_ENDP_1_CTL 155 
#define  TP6800_R2F_TIMING_CFG 154 
#define  TP6800_R30_SENSOR_CFG 153 
#define  TP6800_R31_PIXEL_START 152 
#define  TP6800_R32_PIXEL_END_L 151 
#define  TP6800_R33_PIXEL_END_H 150 
#define  TP6800_R34_LINE_START 149 
#define  TP6800_R35_LINE_END_L 148 
#define  TP6800_R36_LINE_END_H 147 
#define  TP6800_R37_FRONT_DARK_ST 146 
#define  TP6800_R38_FRONT_DARK_END 145 
#define  TP6800_R39_REAR_DARK_ST_L 144 
#define  TP6800_R3A_REAR_DARK_ST_H 143 
#define  TP6800_R3B_REAR_DARK_END_L 142 
#define  TP6800_R3C_REAR_DARK_END_H 141 
#define  TP6800_R3D_HORIZ_DARK_LINE_L 140 
#define  TP6800_R3E_HORIZ_DARK_LINE_H 139 
#define  TP6800_R3F_FRAME_RATE 138 
#define  TP6800_R50 137 
#define  TP6800_R51 136 
#define  TP6800_R52 135 
#define  TP6800_R53 134 
#define  TP6800_R54_DARK_CFG 133 
#define  TP6800_R5C_EDGE_THRLD 132 
#define  TP6800_R5D_DEMOSAIC_CFG 131 
#define  TP6800_R78_FORMAT 130 
#define  TP6800_R79_QUALITY 129 
#define  TP6800_R7A_BLK_THRLD 128 
 int /*<<< orphan*/  bulk_w (struct gspca_dev*,int,struct cmd const*,int /*<<< orphan*/ ) ; 
 struct cmd const** color_gain ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  i2c_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int const,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  setexposure (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setgamma (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setquality (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsharpness (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soi763a_6800_start(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const struct cmd reg_init[] = {
		{TP6800_R79_QUALITY, 0x04},
		{TP6800_R79_QUALITY, 0x01},
		{TP6800_R10_SIF_TYPE, 0x00},	/* i2c 8 bits */

		{TP6800_R50, 0x00},
		{TP6800_R51, 0x00},
		{TP6800_R52, 0xff},
		{TP6800_R53, 0x03},
		{TP6800_R54_DARK_CFG, 0x07},
		{TP6800_R5C_EDGE_THRLD, 0x40},

		{TP6800_R79_QUALITY, 0x03},
		{TP6800_R7A_BLK_THRLD, 0x40},

		{TP6800_R2F_TIMING_CFG, 0x46},
		{TP6800_R30_SENSOR_CFG, 0x10},	/* BG1..G0R */
		{TP6800_R37_FRONT_DARK_ST, 0x00},
		{TP6800_R38_FRONT_DARK_END, 0x00},
		{TP6800_R39_REAR_DARK_ST_L, 0x00},
		{TP6800_R3A_REAR_DARK_ST_H, 0x00},
		{TP6800_R3B_REAR_DARK_END_L, 0x00},
		{TP6800_R3C_REAR_DARK_END_H, 0x00},
		{TP6800_R3D_HORIZ_DARK_LINE_L, 0x00},
		{TP6800_R3E_HORIZ_DARK_LINE_H, 0x00},
		{TP6800_R21_ENDP_1_CTL, 0x03},

		{TP6800_R3F_FRAME_RATE, 0x04},	/* 15 fps */
		{TP6800_R5D_DEMOSAIC_CFG, 0x0e}, /* scale down - medium edge */

		{TP6800_R31_PIXEL_START, 0x1b},
		{TP6800_R32_PIXEL_END_L, 0x9a},
		{TP6800_R33_PIXEL_END_H, 0x02},
		{TP6800_R34_LINE_START, 0x0f},
		{TP6800_R35_LINE_END_L, 0xf4},
		{TP6800_R36_LINE_END_H, 0x01},
		{TP6800_R78_FORMAT, 0x01},	/* qvga */
		{TP6800_R12_SIF_ADDR_S, 0x21},	/* soi763a i2c addr */
		{TP6800_R1A_SIF_TX_DATA2, 0x00},
	};
	static const struct cmd sensor_init[] = {
		{0x12, 0x48},		/* mirror - RGB */
		{0x13, 0xa0},		/* clock - no AGC nor AEC */
		{0x03, 0xa4},		/* saturation */
		{0x04, 0x30},		/* hue */
		{0x05, 0x88},		/* contrast */
		{0x06, 0x60},		/* brightness */
		{0x10, 0x41},		/* AEC */
		{0x11, 0x40},		/* clock rate */
		{0x13, 0xa0},
		{0x14, 0x00},		/* 640x480 */
		{0x15, 0x14},
		{0x1f, 0x41},
		{0x20, 0x80},
		{0x23, 0xee},
		{0x24, 0x50},
		{0x25, 0x7a},
		{0x26, 0x00},
		{0x27, 0xe2},
		{0x28, 0xb0},
		{0x2a, 0x00},
		{0x2b, 0x00},
		{0x2d, 0x81},
		{0x2f, 0x9d},
		{0x60, 0x80},
		{0x61, 0x00},
		{0x62, 0x88},
		{0x63, 0x11},
		{0x64, 0x89},
		{0x65, 0x00},
		{0x67, 0x94},
		{0x68, 0x7a},
		{0x69, 0x0f},
		{0x6c, 0x80},
		{0x6d, 0x80},
		{0x6e, 0x80},
		{0x6f, 0xff},
		{0x71, 0x20},
		{0x74, 0x20},
		{0x75, 0x86},
		{0x77, 0xb5},
		{0x17, 0x18},		/* H href start */
		{0x18, 0xbf},		/* H href end */
		{0x19, 0x03},		/* V start */
		{0x1a, 0xf8},		/* V end */
		{0x01, 0x80},		/* blue gain */
		{0x02, 0x80},		/* red gain */
	};

	reg_w_buf(gspca_dev, reg_init, ARRAY_SIZE(reg_init));

	i2c_w(gspca_dev, 0x12, 0x80);		/* sensor reset */
	msleep(10);

	i2c_w_buf(gspca_dev, sensor_init, ARRAY_SIZE(sensor_init));

	reg_w(gspca_dev, TP6800_R5C_EDGE_THRLD, 0x10);
	reg_w(gspca_dev, TP6800_R54_DARK_CFG, 0x00);

	setsharpness(gspca_dev, v4l2_ctrl_g_ctrl(sd->sharpness));

	bulk_w(gspca_dev, 0x03, color_gain[SENSOR_SOI763A],
				ARRAY_SIZE(color_gain[0]));

	set_led(gspca_dev, 1);
	if (sd->sensor == SENSOR_CX0342)
		setexposure(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->exposure),
			v4l2_ctrl_g_ctrl(gspca_dev->gain),
			v4l2_ctrl_g_ctrl(sd->blue),
			v4l2_ctrl_g_ctrl(sd->red));
	else
		setexposure(gspca_dev, v4l2_ctrl_g_ctrl(gspca_dev->exposure),
			v4l2_ctrl_g_ctrl(gspca_dev->gain), 0, 0);
	if (sd->sensor == SENSOR_SOI763A)
		setquality(gspca_dev, v4l2_ctrl_g_ctrl(sd->jpegqual));
	setgamma(gspca_dev, v4l2_ctrl_g_ctrl(sd->gamma));
}