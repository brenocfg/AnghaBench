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
struct input_dev {int /*<<< orphan*/  users; } ;
struct device {int dummy; } ;
struct cyapa {scalar_t__ operational; TYPE_2__* ops; struct input_dev* input; TYPE_1__* client; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_power_mode ) (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CYAPA_PM_ACTIVE ; 
 int /*<<< orphan*/  CYAPA_PM_DEACTIVE ; 
 int /*<<< orphan*/  PWR_MODE_FULL_ACTIVE ; 
 int /*<<< orphan*/  PWR_MODE_OFF ; 
 int cyapa_create_input_dev (struct cyapa*) ; 
 int cyapa_detect (struct cyapa*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 scalar_t__ pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct cyapa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyapa_reinitialize(struct cyapa *cyapa)
{
	struct device *dev = &cyapa->client->dev;
	struct input_dev *input = cyapa->input;
	int error;

	if (pm_runtime_enabled(dev))
		pm_runtime_disable(dev);

	/* Avoid command failures when TP was in OFF state. */
	if (cyapa->operational)
		cyapa->ops->set_power_mode(cyapa,
				PWR_MODE_FULL_ACTIVE, 0, CYAPA_PM_ACTIVE);

	error = cyapa_detect(cyapa);
	if (error)
		goto out;

	if (!input && cyapa->operational) {
		error = cyapa_create_input_dev(cyapa);
		if (error) {
			dev_err(dev, "create input_dev instance failed: %d\n",
					error);
			goto out;
		}
	}

out:
	if (!input || !input->users) {
		/* Reset to power OFF state to save power when no user open. */
		if (cyapa->operational)
			cyapa->ops->set_power_mode(cyapa,
					PWR_MODE_OFF, 0, CYAPA_PM_DEACTIVE);
	} else if (!error && cyapa->operational) {
		/*
		 * Make sure only enable runtime PM when device is
		 * in operational mode and input->users > 0.
		 */
		pm_runtime_set_active(dev);
		pm_runtime_enable(dev);

		pm_runtime_get_sync(dev);
		pm_runtime_mark_last_busy(dev);
		pm_runtime_put_sync_autosuspend(dev);
	}

	return error;
}