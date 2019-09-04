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
struct cyapa {int /*<<< orphan*/  state_sync_lock; TYPE_1__* ops; scalar_t__ operational; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power_mode ) (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_PM_DEACTIVE ; 
 int /*<<< orphan*/  PWR_MODE_OFF ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct cyapa* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 scalar_t__ pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyapa_close(struct input_dev *input)
{
	struct cyapa *cyapa = input_get_drvdata(input);
	struct i2c_client *client = cyapa->client;
	struct device *dev = &cyapa->client->dev;

	mutex_lock(&cyapa->state_sync_lock);

	disable_irq(client->irq);
	if (pm_runtime_enabled(dev))
		pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);

	if (cyapa->operational)
		cyapa->ops->set_power_mode(cyapa,
				PWR_MODE_OFF, 0, CYAPA_PM_DEACTIVE);

	mutex_unlock(&cyapa->state_sync_lock);
}