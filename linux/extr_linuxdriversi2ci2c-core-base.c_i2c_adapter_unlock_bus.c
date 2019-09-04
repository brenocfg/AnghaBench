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
struct i2c_adapter {int /*<<< orphan*/  bus_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2c_adapter_unlock_bus(struct i2c_adapter *adapter,
				   unsigned int flags)
{
	rt_mutex_unlock(&adapter->bus_lock);
}