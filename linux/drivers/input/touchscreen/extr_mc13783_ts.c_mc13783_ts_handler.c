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
struct mc13783_ts_priv {int /*<<< orphan*/  work; int /*<<< orphan*/  mc13xxx; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  mc13xxx_irq_ack (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mc13783_ts_handler(int irq, void *data)
{
	struct mc13783_ts_priv *priv = data;

	mc13xxx_irq_ack(priv->mc13xxx, irq);

	/*
	 * Kick off reading coordinates. Note that if work happens already
	 * be queued for future execution (it rearms itself) it will not
	 * be rescheduled for immediate execution here. However the rearm
	 * delay is HZ / 50 which is acceptable.
	 */
	schedule_delayed_work(&priv->work, 0);

	return IRQ_HANDLED;
}