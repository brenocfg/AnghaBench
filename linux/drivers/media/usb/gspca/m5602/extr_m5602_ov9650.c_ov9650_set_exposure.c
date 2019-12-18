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
 int /*<<< orphan*/  OV9650_AECH ; 
 int /*<<< orphan*/  OV9650_AECHM ; 
 int /*<<< orphan*/  OV9650_COM1 ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int m5602_write_sensor (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ov9650_set_exposure(struct gspca_dev *gspca_dev, __s32 val)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 i2c_data;
	int err;

	gspca_dbg(gspca_dev, D_CONF, "Set exposure to %d\n", val);

	/* The 6 MSBs */
	i2c_data = (val >> 10) & 0x3f;
	err = m5602_write_sensor(sd, OV9650_AECHM,
				  &i2c_data, 1);
	if (err < 0)
		return err;

	/* The 8 middle bits */
	i2c_data = (val >> 2) & 0xff;
	err = m5602_write_sensor(sd, OV9650_AECH,
				  &i2c_data, 1);
	if (err < 0)
		return err;

	/* The 2 LSBs */
	i2c_data = val & 0x03;
	err = m5602_write_sensor(sd, OV9650_COM1, &i2c_data, 1);
	return err;
}