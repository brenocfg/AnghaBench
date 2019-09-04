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
struct as10x_bus_adapter_t {int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct as102_dev_t {struct as10x_bus_adapter_t bus_adap; } ;
struct TYPE_2__ {int (* start_stream ) (struct as102_dev_t*) ;} ;

/* Variables and functions */
 int EFAULT ; 
 int as10x_cmd_start_streaming (struct as10x_bus_adapter_t*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct as102_dev_t*) ; 
 scalar_t__ ts_auto_disable ; 

__attribute__((used)) static int as102_start_stream(struct as102_dev_t *dev)
{
	struct as10x_bus_adapter_t *bus_adap;
	int ret = -EFAULT;

	if (dev != NULL)
		bus_adap = &dev->bus_adap;
	else
		return ret;

	if (bus_adap->ops->start_stream != NULL)
		ret = bus_adap->ops->start_stream(dev);

	if (ts_auto_disable) {
		if (mutex_lock_interruptible(&dev->bus_adap.lock))
			return -EFAULT;

		ret = as10x_cmd_start_streaming(bus_adap);

		mutex_unlock(&dev->bus_adap.lock);
	}

	return ret;
}