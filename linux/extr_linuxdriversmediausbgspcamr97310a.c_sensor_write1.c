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
struct sd {scalar_t__ cam_type; scalar_t__ sensor_type; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ CAM_TYPE_CIF ; 
 int sensor_write_reg (struct gspca_dev*,int,int,int*,int) ; 

__attribute__((used)) static int sensor_write1(struct gspca_dev *gspca_dev, u8 reg, u8 data)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 buf, confirm_reg;
	int rc;

	buf = data;
	if (sd->cam_type == CAM_TYPE_CIF) {
		rc = sensor_write_reg(gspca_dev, reg, 0x01, &buf, 1);
		confirm_reg = sd->sensor_type ? 0x13 : 0x11;
	} else {
		rc = sensor_write_reg(gspca_dev, reg, 0x00, &buf, 1);
		confirm_reg = 0x11;
	}
	if (rc < 0)
		return rc;

	buf = 0x01;
	rc = sensor_write_reg(gspca_dev, confirm_reg, 0x00, &buf, 1);
	if (rc < 0)
		return rc;

	return 0;
}