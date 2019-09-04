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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PO1030_AUTOCTRL1 ; 
 int V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int m5602_read_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int po1030_set_auto_exposure(struct gspca_dev *gspca_dev,
				    __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 i2c_data;
	int err;

	err = m5602_read_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
	if (err < 0)
		return err;

	gspca_dbg(gspca_dev, D_CONF, "Set auto exposure to %d\n", val);
	val = (val == V4L2_EXPOSURE_AUTO);
	i2c_data = (i2c_data & 0xfd) | ((val & 0x01) << 1);
	return m5602_write_sensor(sd, PO1030_AUTOCTRL1, &i2c_data, 1);
}