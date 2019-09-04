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
struct sd {scalar_t__ bridge; scalar_t__ sensor; } ;
struct gspca_dev {int usb_err; scalar_t__ curr_mode; } ;
struct cmd {int member_0; int member_1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct cmd const*) ; 
 scalar_t__ BRIDGE_TP6800 ; 
#define  CX0342_AUTO_ADC_CALIB 136 
#define  CX0342_EXPO_LINE_H 135 
#define  CX0342_EXPO_LINE_L 134 
#define  CX0342_RAW_BGAIN_L 133 
#define  CX0342_RAW_GBGAIN_L 132 
#define  CX0342_RAW_GRGAIN_L 131 
#define  CX0342_RAW_RGAIN_L 130 
#define  CX0342_SYS_CTRL_0 129 
 scalar_t__ SENSOR_CX0342 ; 
 int TP6800_R12_SIF_ADDR_S ; 
#define  TP6800_R3F_FRAME_RATE 128 
 int TP6800_R78_FORMAT ; 
 int /*<<< orphan*/  bulk_w (struct gspca_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  color_null ; 
 int /*<<< orphan*/  i2c_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int const,int) ; 
 int /*<<< orphan*/  reg_w_buf (struct gspca_dev*,struct cmd const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_isoc_init(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	static const struct cmd cx_sensor_init[] = {
		{CX0342_AUTO_ADC_CALIB, 0x81},
		{CX0342_EXPO_LINE_L, 0x37},
		{CX0342_EXPO_LINE_H, 0x01},
		{CX0342_RAW_GRGAIN_L, 0x00},
		{CX0342_RAW_GBGAIN_L, 0x00},
		{CX0342_RAW_RGAIN_L, 0x00},
		{CX0342_RAW_BGAIN_L, 0x00},
		{CX0342_SYS_CTRL_0, 0x81},
	};
	static const struct cmd cx_bridge_init[] = {
		{0x4d, 0x00},
		{0x4c, 0xff},
		{0x4e, 0xff},
		{0x4f, 0x00},
	};
	static const struct cmd ov_sensor_init[] = {
		{0x10, 0x75},		/* exposure */
		{0x76, 0x03},
		{0x00, 0x00},		/* gain */
	};
	static const struct cmd ov_bridge_init[] = {
		{0x7b, 0x90},
		{TP6800_R3F_FRAME_RATE, 0x87},
	};

	if (sd->bridge == BRIDGE_TP6800)
		return 0;
	if (sd->sensor == SENSOR_CX0342) {
		reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x20);
		reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, 0x87);
		i2c_w_buf(gspca_dev, cx_sensor_init,
				ARRAY_SIZE(cx_sensor_init));
		reg_w_buf(gspca_dev, cx_bridge_init,
				ARRAY_SIZE(cx_bridge_init));
		bulk_w(gspca_dev, 0x03, color_null, sizeof color_null);
		reg_w(gspca_dev, 0x59, 0x40);
	} else {
		reg_w(gspca_dev, TP6800_R12_SIF_ADDR_S, 0x21);
		i2c_w_buf(gspca_dev, ov_sensor_init,
				ARRAY_SIZE(ov_sensor_init));
		reg_r(gspca_dev, 0x7b);
		reg_w_buf(gspca_dev, ov_bridge_init,
				ARRAY_SIZE(ov_bridge_init));
	}
	reg_w(gspca_dev, TP6800_R78_FORMAT,
			gspca_dev->curr_mode ? 0x00 : 0x01);
	return gspca_dev->usb_err;
}