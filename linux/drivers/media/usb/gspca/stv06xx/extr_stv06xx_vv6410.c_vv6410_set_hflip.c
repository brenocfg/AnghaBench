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
typedef  int /*<<< orphan*/  u16 ;
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  VV6410_DATAFORMAT ; 
 int /*<<< orphan*/  VV6410_HFLIP ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int stv06xx_read_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vv6410_set_hflip(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	u16 i2c_data;
	struct sd *sd = (struct sd *) gspca_dev;

	err = stv06xx_read_sensor(sd, VV6410_DATAFORMAT, &i2c_data);
	if (err < 0)
		return err;

	if (val)
		i2c_data |= VV6410_HFLIP;
	else
		i2c_data &= ~VV6410_HFLIP;

	gspca_dbg(gspca_dev, D_CONF, "Set horizontal flip to %d\n", val);
	err = stv06xx_write_sensor(sd, VV6410_DATAFORMAT, i2c_data);

	return (err < 0) ? err : 0;
}