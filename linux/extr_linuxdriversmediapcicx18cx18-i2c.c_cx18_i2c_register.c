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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {scalar_t__ grp_id; } ;
struct i2c_adapter {int dummy; } ;
struct cx18 {int /*<<< orphan*/  v4l2_dev; TYPE_1__* card_i2c; struct i2c_adapter* i2c_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tv; int /*<<< orphan*/ * demod; int /*<<< orphan*/ * radio; } ;

/* Variables and functions */
 scalar_t__ CX18_HW_TUNER ; 
 scalar_t__ CX18_HW_Z8F0811_IR_HAUP ; 
 int cx18_i2c_new_ir (struct cx18*,struct i2c_adapter*,scalar_t__,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hw_addrs ; 
 int* hw_bus ; 
 char** hw_devicenames ; 
 struct v4l2_subdev* v4l2_i2c_new_subdev (int /*<<< orphan*/ *,struct i2c_adapter*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int cx18_i2c_register(struct cx18 *cx, unsigned idx)
{
	struct v4l2_subdev *sd;
	int bus = hw_bus[idx];
	struct i2c_adapter *adap = &cx->i2c_adap[bus];
	const char *type = hw_devicenames[idx];
	u32 hw = 1 << idx;

	if (hw == CX18_HW_TUNER) {
		/* special tuner group handling */
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->radio);
		if (sd != NULL)
			sd->grp_id = hw;
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->demod);
		if (sd != NULL)
			sd->grp_id = hw;
		sd = v4l2_i2c_new_subdev(&cx->v4l2_dev,
				adap, type, 0, cx->card_i2c->tv);
		if (sd != NULL)
			sd->grp_id = hw;
		return sd != NULL ? 0 : -1;
	}

	if (hw == CX18_HW_Z8F0811_IR_HAUP)
		return cx18_i2c_new_ir(cx, adap, hw, type, hw_addrs[idx]);

	/* Is it not an I2C device or one we do not wish to register? */
	if (!hw_addrs[idx])
		return -1;

	/* It's an I2C device other than an analog tuner or IR chip */
	sd = v4l2_i2c_new_subdev(&cx->v4l2_dev, adap, type, hw_addrs[idx],
				 NULL);
	if (sd != NULL)
		sd->grp_id = hw;
	return sd != NULL ? 0 : -1;
}