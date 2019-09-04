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
struct sd {int dummy; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  VV6410_ANALOGGAIN ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vv6410_set_analog_gain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;

	gspca_dbg(gspca_dev, D_CONF, "Set analog gain to %d\n", val);
	err = stv06xx_write_sensor(sd, VV6410_ANALOGGAIN, 0xf0 | (val & 0xf));

	return (err < 0) ? err : 0;
}