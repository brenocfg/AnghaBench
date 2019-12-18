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
struct rmi_driver_data {int enabled; int /*<<< orphan*/  enabled_mutex; int /*<<< orphan*/  attn_fifo; } ;
struct rmi_device_platform_data {int irq; } ;
struct rmi_device {int /*<<< orphan*/  dev; TYPE_1__* xport; } ;
struct rmi4_attn_data {int /*<<< orphan*/  data; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct rmi_driver_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int) ; 
 int enable_irq_wake (int) ; 
 int kfifo_get (int /*<<< orphan*/ *,struct rmi4_attn_data*) ; 
 int /*<<< orphan*/  kfifo_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rmi_device_platform_data* rmi_get_platform_data (struct rmi_device*) ; 

void rmi_disable_irq(struct rmi_device *rmi_dev, bool enable_wake)
{
	struct rmi_device_platform_data *pdata = rmi_get_platform_data(rmi_dev);
	struct rmi_driver_data *data = dev_get_drvdata(&rmi_dev->dev);
	struct rmi4_attn_data attn_data = {0};
	int irq = pdata->irq;
	int retval, count;

	mutex_lock(&data->enabled_mutex);

	if (!data->enabled)
		goto out;

	data->enabled = false;
	disable_irq(irq);
	if (enable_wake && device_may_wakeup(rmi_dev->xport->dev)) {
		retval = enable_irq_wake(irq);
		if (retval)
			dev_warn(&rmi_dev->dev,
				 "Failed to enable irq for wake: %d\n",
				 retval);
	}

	/* make sure the fifo is clean */
	while (!kfifo_is_empty(&data->attn_fifo)) {
		count = kfifo_get(&data->attn_fifo, &attn_data);
		if (count)
			kfree(attn_data.data);
	}

out:
	mutex_unlock(&data->enabled_mutex);
}