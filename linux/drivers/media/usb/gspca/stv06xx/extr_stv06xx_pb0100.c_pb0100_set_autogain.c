#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd {struct pb0100_ctrls* sensor_priv; } ;
struct pb0100_ctrls {TYPE_1__* natural; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PB_EXPGAIN ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,scalar_t__,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_set_autogain(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	struct pb0100_ctrls *ctrls = sd->sensor_priv;

	if (val) {
		if (ctrls->natural->val)
			val = BIT(6)|BIT(4)|BIT(0);
		else
			val = BIT(4)|BIT(0);
	} else
		val = 0;

	err = stv06xx_write_sensor(sd, PB_EXPGAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set autogain to %d (natural: %d), status: %d\n",
		  val, ctrls->natural->val, err);

	return err;
}