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
struct device {int dummy; } ;
struct cyapa {int /*<<< orphan*/  state_sync_lock; TYPE_2__* ops; scalar_t__ operational; int /*<<< orphan*/  input; TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int (* irq_handler ) (struct cyapa*) ;int /*<<< orphan*/  (* sort_empty_output_data ) (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ (* irq_cmd_handler ) (struct cyapa*) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cyapa_reinitialize (struct cyapa*) ; 
 scalar_t__ device_may_wakeup (struct device*) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_wakeup_event (struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct cyapa*) ; 
 int /*<<< orphan*/  stub2 (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub3 (struct cyapa*) ; 
 int /*<<< orphan*/  stub4 (struct cyapa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cyapa_irq(int irq, void *dev_id)
{
	struct cyapa *cyapa = dev_id;
	struct device *dev = &cyapa->client->dev;
	int error;

	if (device_may_wakeup(dev))
		pm_wakeup_event(dev, 0);

	/* Interrupt event can be caused by host command to trackpad device. */
	if (cyapa->ops->irq_cmd_handler(cyapa)) {
		/*
		 * Interrupt event maybe from trackpad device input reporting.
		 */
		if (!cyapa->input) {
			/*
			 * Still in probing or in firmware image
			 * updating or reading.
			 */
			cyapa->ops->sort_empty_output_data(cyapa,
					NULL, NULL, NULL);
			goto out;
		}

		if (cyapa->operational) {
			error = cyapa->ops->irq_handler(cyapa);

			/*
			 * Apply runtime power management to touch report event
			 * except the events caused by the command responses.
			 * Note:
			 * It will introduce about 20~40 ms additional delay
			 * time in receiving for first valid touch report data.
			 * The time is used to execute device runtime resume
			 * process.
			 */
			pm_runtime_get_sync(dev);
			pm_runtime_mark_last_busy(dev);
			pm_runtime_put_sync_autosuspend(dev);
		}

		if (!cyapa->operational || error) {
			if (!mutex_trylock(&cyapa->state_sync_lock)) {
				cyapa->ops->sort_empty_output_data(cyapa,
					NULL, NULL, NULL);
				goto out;
			}
			cyapa_reinitialize(cyapa);
			mutex_unlock(&cyapa->state_sync_lock);
		}
	}

out:
	return IRQ_HANDLED;
}