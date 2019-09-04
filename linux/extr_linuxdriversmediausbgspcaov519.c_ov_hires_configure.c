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
struct sd {scalar_t__ bridge; int /*<<< orphan*/  sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BRIDGE_OVFX2 ; 
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  SEN_OV2610 ; 
 int /*<<< orphan*/  SEN_OV2610AE ; 
 int /*<<< orphan*/  SEN_OV3610 ; 
 int /*<<< orphan*/  SEN_OV9600 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,...) ; 
 int i2c_r (struct sd*,int) ; 

__attribute__((used)) static void ov_hires_configure(struct sd *sd)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int high, low;

	if (sd->bridge != BRIDGE_OVFX2) {
		gspca_err(gspca_dev, "error hires sensors only supported with ovfx2\n");
		return;
	}

	gspca_dbg(gspca_dev, D_PROBE, "starting ov hires configuration\n");

	/* Detect sensor (sub)type */
	high = i2c_r(sd, 0x0a);
	low = i2c_r(sd, 0x0b);
	/* info("%x, %x", high, low); */
	switch (high) {
	case 0x96:
		switch (low) {
		case 0x40:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV2610\n");
			sd->sensor = SEN_OV2610;
			return;
		case 0x41:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV2610AE\n");
			sd->sensor = SEN_OV2610AE;
			return;
		case 0xb1:
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV9600\n");
			sd->sensor = SEN_OV9600;
			return;
		}
		break;
	case 0x36:
		if ((low & 0x0f) == 0x00) {
			gspca_dbg(gspca_dev, D_PROBE, "Sensor is a OV3610\n");
			sd->sensor = SEN_OV3610;
			return;
		}
		break;
	}
	gspca_err(gspca_dev, "Error unknown sensor type: %02x%02x\n",
		  high, low);
}