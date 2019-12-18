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
struct i2c_adapter {int dummy; } ;
struct i3c_master_controller {struct i2c_adapter i2c; } ;

/* Variables and functions */

__attribute__((used)) static struct i2c_adapter *
i3c_master_to_i2c_adapter(struct i3c_master_controller *master)
{
	return &master->i2c;
}