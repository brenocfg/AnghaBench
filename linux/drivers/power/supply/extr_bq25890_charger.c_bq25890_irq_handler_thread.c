#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct bq25890_state {int dummy; } ;
struct bq25890_device {int /*<<< orphan*/  charger; int /*<<< orphan*/  lock; struct bq25890_state state; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int bq25890_get_chip_state (struct bq25890_device*,struct bq25890_state*) ; 
 int /*<<< orphan*/  bq25890_handle_state_change (struct bq25890_device*,struct bq25890_state*) ; 
 int /*<<< orphan*/  bq25890_state_changed (struct bq25890_device*,struct bq25890_state*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t bq25890_irq_handler_thread(int irq, void *private)
{
	struct bq25890_device *bq = private;
	int ret;
	struct bq25890_state state;

	ret = bq25890_get_chip_state(bq, &state);
	if (ret < 0)
		goto handled;

	if (!bq25890_state_changed(bq, &state))
		goto handled;

	bq25890_handle_state_change(bq, &state);

	mutex_lock(&bq->lock);
	bq->state = state;
	mutex_unlock(&bq->lock);

	power_supply_changed(bq->charger);

handled:
	return IRQ_HANDLED;
}