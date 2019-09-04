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
struct wakeup_source {struct wake_irq* wakeirq; } ;
struct wake_irq {int dummy; } ;
struct TYPE_2__ {struct wakeup_source* wakeup; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

void device_wakeup_attach_irq(struct device *dev,
			     struct wake_irq *wakeirq)
{
	struct wakeup_source *ws;

	ws = dev->power.wakeup;
	if (!ws)
		return;

	if (ws->wakeirq)
		dev_err(dev, "Leftover wakeup IRQ found, overriding\n");

	ws->wakeirq = wakeirq;
}