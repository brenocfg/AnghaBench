#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct as10x_bus_adapter_t {int /*<<< orphan*/  lock; TYPE_1__* usb_dev; TYPE_2__* ops; } ;
struct as102_dev_t {struct as10x_bus_adapter_t bus_adap; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop_stream ) (struct as102_dev_t*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ as10x_cmd_stop_streaming (struct as10x_bus_adapter_t*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct as102_dev_t*) ; 
 scalar_t__ ts_auto_disable ; 

__attribute__((used)) static void as102_stop_stream(struct as102_dev_t *dev)
{
	struct as10x_bus_adapter_t *bus_adap;

	if (dev != NULL)
		bus_adap = &dev->bus_adap;
	else
		return;

	if (bus_adap->ops->stop_stream != NULL)
		bus_adap->ops->stop_stream(dev);

	if (ts_auto_disable) {
		if (mutex_lock_interruptible(&dev->bus_adap.lock))
			return;

		if (as10x_cmd_stop_streaming(bus_adap) < 0)
			dev_dbg(&dev->bus_adap.usb_dev->dev,
				"as10x_cmd_stop_streaming failed\n");

		mutex_unlock(&dev->bus_adap.lock);
	}
}