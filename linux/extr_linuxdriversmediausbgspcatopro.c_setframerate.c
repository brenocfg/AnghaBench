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
struct sd {scalar_t__ bridge; scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 scalar_t__ BRIDGE_TP6810 ; 
 int /*<<< orphan*/  CX0342_AUTO_ADC_CALIB ; 
 scalar_t__ SENSOR_CX0342 ; 
 int TP6800_R3F_FRAME_RATE ; 
 int get_fr_idx (struct gspca_dev*) ; 
 int /*<<< orphan*/  i2c_w (struct gspca_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reg_r (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  reg_w (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void setframerate(struct gspca_dev *gspca_dev, s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 fr_idx;

	fr_idx = get_fr_idx(gspca_dev);

	if (sd->bridge == BRIDGE_TP6810) {
		reg_r(gspca_dev, 0x7b);
		reg_w(gspca_dev, 0x7b,
			sd->sensor == SENSOR_CX0342 ? 0x10 : 0x90);
		if (val >= 128)
			fr_idx = 0xf0;		/* lower frame rate */
	}

	reg_w(gspca_dev, TP6800_R3F_FRAME_RATE, fr_idx);

	if (sd->sensor == SENSOR_CX0342)
		i2c_w(gspca_dev, CX0342_AUTO_ADC_CALIB, 0x01);
}