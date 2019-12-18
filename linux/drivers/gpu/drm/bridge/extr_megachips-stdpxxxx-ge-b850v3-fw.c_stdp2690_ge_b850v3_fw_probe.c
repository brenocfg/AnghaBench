#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_3__ {struct i2c_client* stdp2690_i2c; } ;

/* Variables and functions */
 int /*<<< orphan*/  ge_b850v3_lvds_init (struct device*) ; 
 TYPE_1__* ge_b850v3_lvds_ptr ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,TYPE_1__*) ; 

__attribute__((used)) static int stdp2690_ge_b850v3_fw_probe(struct i2c_client *stdp2690_i2c,
				       const struct i2c_device_id *id)
{
	struct device *dev = &stdp2690_i2c->dev;

	ge_b850v3_lvds_init(dev);

	ge_b850v3_lvds_ptr->stdp2690_i2c = stdp2690_i2c;
	i2c_set_clientdata(stdp2690_i2c, ge_b850v3_lvds_ptr);

	return 0;
}