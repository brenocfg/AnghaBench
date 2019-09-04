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
struct as10x_tune_args {int dummy; } ;
struct as10x_bus_adapter_t {int /*<<< orphan*/  lock; TYPE_1__* usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int as10x_cmd_set_tune (struct as10x_bus_adapter_t*,struct as10x_tune_args*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as102_set_tune(void *priv, struct as10x_tune_args *tune_args)
{
	struct as10x_bus_adapter_t *bus_adap = priv;
	int ret;

	/* Set frontend arguments */
	if (mutex_lock_interruptible(&bus_adap->lock))
		return -EBUSY;

	ret =  as10x_cmd_set_tune(bus_adap, tune_args);
	if (ret != 0)
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_set_tune failed. (err = %d)\n", ret);

	mutex_unlock(&bus_adap->lock);

	return ret;
}