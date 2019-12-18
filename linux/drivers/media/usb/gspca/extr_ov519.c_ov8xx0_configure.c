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
struct sd {int /*<<< orphan*/  sensor; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PROBE ; 
 int /*<<< orphan*/  OV7610_REG_COM_I ; 
 int /*<<< orphan*/  SEN_OV8610 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gspca_err (struct gspca_dev*,char*,...) ; 
 int i2c_r (struct sd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov8xx0_configure(struct sd *sd)
{
	struct gspca_dev *gspca_dev = (struct gspca_dev *)sd;
	int rc;

	gspca_dbg(gspca_dev, D_PROBE, "starting ov8xx0 configuration\n");

	/* Detect sensor (sub)type */
	rc = i2c_r(sd, OV7610_REG_COM_I);
	if (rc < 0) {
		gspca_err(gspca_dev, "Error detecting sensor type\n");
		return;
	}
	if ((rc & 3) == 1)
		sd->sensor = SEN_OV8610;
	else
		gspca_err(gspca_dev, "Unknown image sensor version: %d\n",
			  rc & 3);
}