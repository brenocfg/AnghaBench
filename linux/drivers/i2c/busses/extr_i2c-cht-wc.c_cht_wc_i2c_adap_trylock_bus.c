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
 int rt_mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cht_wc_i2c_adap_trylock_bus(struct i2c_adapter *adapter,
				   unsigned int flags)
{
	return rt_mutex_trylock(&adapter->bus_lock);
}