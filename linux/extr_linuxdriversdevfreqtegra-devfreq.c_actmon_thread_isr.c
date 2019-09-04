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
struct tegra_devfreq {TYPE_1__* devfreq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_devfreq (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t actmon_thread_isr(int irq, void *data)
{
	struct tegra_devfreq *tegra = data;

	mutex_lock(&tegra->devfreq->lock);
	update_devfreq(tegra->devfreq);
	mutex_unlock(&tegra->devfreq->lock);

	return IRQ_HANDLED;
}