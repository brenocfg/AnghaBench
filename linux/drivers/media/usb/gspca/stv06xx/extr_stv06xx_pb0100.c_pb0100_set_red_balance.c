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
struct pb0100_ctrls {TYPE_1__* gain; } ;
struct gspca_dev {int dummy; } ;
typedef  int __s32 ;
struct TYPE_2__ {scalar_t__ val; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  PB_RGAIN ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 
 int stv06xx_write_sensor (struct sd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pb0100_set_red_balance(struct gspca_dev *gspca_dev, __s32 val)
{
	int err;
	struct sd *sd = (struct sd *) gspca_dev;
	struct pb0100_ctrls *ctrls = sd->sensor_priv;

	val += ctrls->gain->val;
	if (val < 0)
		val = 0;
	else if (val > 255)
		val = 255;

	err = stv06xx_write_sensor(sd, PB_RGAIN, val);
	gspca_dbg(gspca_dev, D_CONF, "Set red gain to %d, status: %d\n",
		  val, err);

	return err;
}