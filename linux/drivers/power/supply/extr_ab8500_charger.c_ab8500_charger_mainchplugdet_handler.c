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
struct ab8500_charger {int /*<<< orphan*/  ac_charger_attached_work; int /*<<< orphan*/  charger_wq; int /*<<< orphan*/  parent; int /*<<< orphan*/  charger_attached_mutex; int /*<<< orphan*/  ac_work; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_ab8500 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ab8500_charger_mainchplugdet_handler(int irq, void *_di)
{
	struct ab8500_charger *di = _di;

	dev_dbg(di->dev, "Main charger plugged\n");
	queue_work(di->charger_wq, &di->ac_work);

	mutex_lock(&di->charger_attached_mutex);
	mutex_unlock(&di->charger_attached_mutex);

	if (is_ab8500(di->parent))
		queue_delayed_work(di->charger_wq,
			   &di->ac_charger_attached_work,
			   HZ);
	return IRQ_HANDLED;
}