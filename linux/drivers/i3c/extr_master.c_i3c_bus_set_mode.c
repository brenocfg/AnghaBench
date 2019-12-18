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
struct i3c_master_controller {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned long i3c; unsigned long i2c; } ;
struct i3c_bus {int mode; TYPE_1__ scl_rate; } ;
typedef  enum i3c_bus_mode { ____Placeholder_i3c_bus_mode } i3c_bus_mode ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long I3C_BUS_I2C_FM_PLUS_SCL_RATE ; 
 unsigned long I3C_BUS_MAX_I3C_SCL_RATE ; 
#define  I3C_BUS_MODE_MIXED_FAST 131 
#define  I3C_BUS_MODE_MIXED_LIMITED 130 
#define  I3C_BUS_MODE_MIXED_SLOW 129 
#define  I3C_BUS_MODE_PURE 128 
 void* I3C_BUS_TYP_I3C_SCL_RATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned long,unsigned long) ; 
 struct i3c_master_controller* i3c_bus_to_i3c_master (struct i3c_bus*) ; 

int i3c_bus_set_mode(struct i3c_bus *i3cbus, enum i3c_bus_mode mode,
		     unsigned long max_i2c_scl_rate)
{
	struct i3c_master_controller *master = i3c_bus_to_i3c_master(i3cbus);

	i3cbus->mode = mode;

	switch (i3cbus->mode) {
	case I3C_BUS_MODE_PURE:
		if (!i3cbus->scl_rate.i3c)
			i3cbus->scl_rate.i3c = I3C_BUS_TYP_I3C_SCL_RATE;
		break;
	case I3C_BUS_MODE_MIXED_FAST:
	case I3C_BUS_MODE_MIXED_LIMITED:
		if (!i3cbus->scl_rate.i3c)
			i3cbus->scl_rate.i3c = I3C_BUS_TYP_I3C_SCL_RATE;
		if (!i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i2c = max_i2c_scl_rate;
		break;
	case I3C_BUS_MODE_MIXED_SLOW:
		if (!i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i2c = max_i2c_scl_rate;
		if (!i3cbus->scl_rate.i3c ||
		    i3cbus->scl_rate.i3c > i3cbus->scl_rate.i2c)
			i3cbus->scl_rate.i3c = i3cbus->scl_rate.i2c;
		break;
	default:
		return -EINVAL;
	}

	dev_dbg(&master->dev, "i2c-scl = %ld Hz i3c-scl = %ld Hz\n",
		i3cbus->scl_rate.i2c, i3cbus->scl_rate.i3c);

	/*
	 * I3C/I2C frequency may have been overridden, check that user-provided
	 * values are not exceeding max possible frequency.
	 */
	if (i3cbus->scl_rate.i3c > I3C_BUS_MAX_I3C_SCL_RATE ||
	    i3cbus->scl_rate.i2c > I3C_BUS_I2C_FM_PLUS_SCL_RATE)
		return -EINVAL;

	return 0;
}