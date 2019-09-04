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
struct input_dev {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
struct cyapa {int /*<<< orphan*/  state_sync_lock; scalar_t__ operational; TYPE_1__* ops; struct i2c_client* client; } ;
struct TYPE_2__ {int (* set_power_mode ) (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_PM_ACTIVE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  PWR_MODE_FULL_ACTIVE ; 
 int cyapa_reinitialize (struct cyapa*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct cyapa* input_get_drvdata (struct input_dev*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int stub1 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyapa_open(struct input_dev *input)
{
	struct cyapa *cyapa = input_get_drvdata(input);
	struct i2c_client *client = cyapa->client;
	struct device *dev = &client->dev;
	int error;

	error = mutex_lock_interruptible(&cyapa->state_sync_lock);
	if (error)
		return error;

	if (cyapa->operational) {
		/*
		 * though failed to set active power mode,
		 * but still may be able to work in lower scan rate
		 * when in operational mode.
		 */
		error = cyapa->ops->set_power_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);
		if (error) {
			dev_warn(dev, "set active power failed: %d\n", error);
			goto out;
		}
	} else {
		error = cyapa_reinitialize(cyapa);
		if (error || !cyapa->operational) {
			error = error ? error : -EAGAIN;
			goto out;
		}
	}

	enable_irq(client->irq);
	if (!pm_runtime_enabled(dev)) {
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);
	}

	pm_runtime_get_sync(dev);
	pm_runtime_mark_last_busy(dev);
	pm_runtime_put_sync_autosuspend(dev);
out:
	mutex_unlock(&cyapa->state_sync_lock);
	return error;
}