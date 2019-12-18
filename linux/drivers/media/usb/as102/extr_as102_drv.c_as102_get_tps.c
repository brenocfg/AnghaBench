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
struct as10x_tps {int dummy; } ;
struct as10x_bus_adapter_t {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int as10x_cmd_get_tps (struct as10x_bus_adapter_t*,struct as10x_tps*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as102_get_tps(void *priv, struct as10x_tps *tps)
{
	struct as10x_bus_adapter_t *bus_adap = priv;
	int ret;

	if (mutex_lock_interruptible(&bus_adap->lock))
		return -EBUSY;

	/* send abilis command: GET_TPS */
	ret = as10x_cmd_get_tps(bus_adap, tps);

	mutex_unlock(&bus_adap->lock);

	return ret;
}