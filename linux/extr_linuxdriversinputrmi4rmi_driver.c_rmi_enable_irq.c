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
struct rmi_driver_data {int enabled; int /*<<< orphan*/  enabled_mutex; } ;
struct rmi_device_platform_data {int irq; } ;
struct rmi_device {int /*<<< orphan*/  dev; TYPE_1__* xport; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQ_TYPE_EDGE_BOTH ; 
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int disable_irq_wake (int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 
 int irq_get_trigger_type (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rmi_device_platform_data* rmi_get_platform_data (struct rmi_device*) ; 
 int /*<<< orphan*/  rmi_process_interrupt_requests (struct rmi_device*) ; 

void rmi_enable_irq(struct rmi_device *rmi_dev, bool clear_wake)
{
	struct rmi_device_platform_data *pdata = rmi_get_platform_data(rmi_dev);
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	int irq = pdata->irq;
	int irq_flags;
	int retval;

	mutex_lock(&data->enabled_mutex);

	if (data->enabled)
		goto out;

	enable_irq(irq);
	data->enabled = true;
	if (clear_wake && device_may_wakeup(rmi_dev->xport->dev)) {
		retval = disable_irq_wake(irq);
		if (retval)
			dev_warn(&rmi_dev->dev,
				 "Failed to disable irq for wake: %d\n",
				 retval);
	}

	/*
	 * Call rmi_process_interrupt_requests() after enabling irq,
	 * otherwise we may lose interrupt on edge-triggered systems.
	 */
	irq_flags = irq_get_trigger_type(pdata->irq);
	if (irq_flags & IRQ_TYPE_EDGE_BOTH)
		rmi_process_interrupt_requests(rmi_dev);

out:
	mutex_unlock(&data->enabled_mutex);
}