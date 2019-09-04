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
struct as10x_tune_status {int dummy; } ;
struct as10x_bus_adapter_t {int /*<<< orphan*/  lock; TYPE_1__* usb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int as10x_cmd_get_tune_status (struct as10x_bus_adapter_t*,struct as10x_tune_status*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int as102_get_status(void *priv, struct as10x_tune_status *tstate)
{
	struct as10x_bus_adapter_t *bus_adap = priv;
	int ret;

	if (mutex_lock_interruptible(&bus_adap->lock))
		return -EBUSY;

	/* send abilis command: GET_TUNE_STATUS */
	ret = as10x_cmd_get_tune_status(bus_adap, tstate);
	if (ret < 0) {
		dev_dbg(&bus_adap->usb_dev->dev,
			"as10x_cmd_get_tune_status failed (err = %d)\n",
			ret);
	}

	mutex_unlock(&bus_adap->lock);

	return ret;
}