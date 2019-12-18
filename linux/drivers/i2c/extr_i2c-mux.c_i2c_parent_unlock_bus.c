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
struct i2c_mux_priv {TYPE_1__* muxc; } ;
struct i2c_adapter {int /*<<< orphan*/  mux_lock; struct i2c_mux_priv* algo_data; } ;
struct TYPE_2__ {struct i2c_adapter* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unlock_bus (struct i2c_adapter*,unsigned int) ; 
 int /*<<< orphan*/  rt_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2c_parent_unlock_bus(struct i2c_adapter *adapter,
				  unsigned int flags)
{
	struct i2c_mux_priv *priv = adapter->algo_data;
	struct i2c_adapter *parent = priv->muxc->parent;

	i2c_unlock_bus(parent, flags);
	rt_mutex_unlock(&parent->mux_lock);
}