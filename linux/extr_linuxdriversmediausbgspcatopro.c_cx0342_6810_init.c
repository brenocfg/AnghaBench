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
struct cmd {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct cmd const*) ; 
#define  CX0342_ADCGN 163 
#define  CX0342_ADC_CTL 162 
#define  CX0342_AUTO_ADC_CALIB 161 
#define  CX0342_BYPASS_MODE 160 
#define  CX0342_CLOCK_GEN 159 
#define  CX0342_DATA_OVERFLOW_H 158 
#define  CX0342_DATA_OVERFLOW_L 157 
#define  CX0342_DATA_UNDERFLOW_H 156 
#define  CX0342_DATA_UNDERFLOW_L 155 
#define  CX0342_GLOBAL_GAIN 154 
#define  CX0342_GPXLTHD_L 153 
#define  CX0342_G_GAP_H 152 
#define  CX0342_G_GAP_L 151 
#define  CX0342_IDLE_CTRL 150 
#define  CX0342_LDOSEL 149 
#define  CX0342_LVRST_BLBIAS 148 
#define  CX0342_OUTPUT_CTRL 147 
#define  CX0342_PLANETHD_H 146 
#define  CX0342_PLANETHD_L 145 
#define  CX0342_RAMP_RIV 144 
#define  CX0342_RBPXLTHD_L 143 
#define  CX0342_RB_GAP_H 142 
#define  CX0342_RB_GAP_L 141 
#define  CX0342_RST_OVERFLOW_H 140 
#define  CX0342_RST_OVERFLOW_L 139 
#define  CX0342_SPV_VALUE_H 138 
#define  CX0342_SPV_VALUE_L 137 
#define  CX0342_SYS_CTRL_0 136 
#define  CX0342_TIMING_EN 135 
#define  CX0342_VTHSEL 134 
#define  TP6800_R11_SIF_CONTROL 133 
 int /*<<< orphan*/  TP6800_R12_SIF_ADDR_S ; 
#define  TP6800_R18_GPIO_DATA 132 
#define  TP6800_R21_ENDP_1_CTL 131 
#define  TP6800_R2F_TIMING_CFG 130 
#define  TP6800_R3F_FRAME_RATE 129 
#define  TP6800_R78_FORMAT 128 
 struct cmd const* cx0342_timing_seq ; 
 int /*<<< orphan*/  i2c_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 struct cmd const* tp6810_cx_init_common ; 

__attribute__((used)) static void cx0342_6810_init(struct gspca_dev *gspca_dev)
{
	static const struct cmd reg_init_1[] = {
		{TP6800_R2F_TIMING_CFG, 0x2f},
		{0x25, 0x02},
		{TP6800_R21_ENDP_1_CTL, 0x00},
		{TP6800_R3F_FRAME_RATE, 0x80},
		{TP6800_R2F_TIMING_CFG, 0x2f},
		{TP6800_R18_GPIO_DATA, 0xe1},
		{TP6800_R18_GPIO_DATA, 0xc1},
		{TP6800_R18_GPIO_DATA, 0xe1},
		{TP6800_R11_SIF_CONTROL, 0x00},
	};
	static const struct cmd reg_init_2[] = {
		{TP6800_R78_FORMAT, 0x48},
		{TP6800_R11_SIF_CONTROL, 0x00},
	};
	static const struct cmd sensor_init[] = {
		{CX0342_OUTPUT_CTRL, 0x07},
		{CX0342_BYPASS_MODE, 0x58},
		{CX0342_GPXLTHD_L, 0x28},
		{CX0342_RBPXLTHD_L, 0x28},
		{CX0342_PLANETHD_L, 0x50},
		{CX0342_PLANETHD_H, 0x03},
		{CX0342_RB_GAP_L, 0xff},
		{CX0342_RB_GAP_H, 0x07},
		{CX0342_G_GAP_L, 0xff},
		{CX0342_G_GAP_H, 0x07},
		{CX0342_RST_OVERFLOW_L, 0x5c},
		{CX0342_RST_OVERFLOW_H, 0x01},
		{CX0342_DATA_OVERFLOW_L, 0xfc},
		{CX0342_DATA_OVERFLOW_H, 0x03},
		{CX0342_DATA_UNDERFLOW_L, 0x00},
		{CX0342_DATA_UNDERFLOW_H, 0x00},
		{CX0342_SYS_CTRL_0, 0x40},
		{CX0342_GLOBAL_GAIN, 0x01},
		{CX0342_CLOCK_GEN, 0x00},
		{CX0342_SYS_CTRL_0, 0x02},
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
		{CX0342_TIMING_EN, 0x01},
	};

	reg_w_buf(gspca_dev, reg_init_1, ARRAY_SIZE(reg_init_1));
	reg_w_buf(gspca_dev, tp6810_cx_init_common,
			ARRAY_SIZE(tp6810_cx_init_common));
	reg_w_buf(gspca_dev, reg_init_2, ARRAY_SIZE(reg_init_2));

	reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x20);	/* cx0342 I2C addr */
	i2c_w_buf(gspca_dev, sensor_init, ARRAY_SIZE(sensor_init));
	i2c_w_buf(gspca_dev, cx0342_timing_seq, ARRAY_SIZE(cx0342_timing_seq));
}