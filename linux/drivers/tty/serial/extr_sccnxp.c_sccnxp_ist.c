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
struct sccnxp_port {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  sccnxp_handle_events (struct sccnxp_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t sccnxp_ist(int irq, void *dev_id)
{
	struct sccnxp_port *s = (struct sccnxp_port *)dev_id;
	unsigned long flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_handle_events(s);
	spin_unlock_irqrestore(&s->lock, flags);

	return IRQ_HANDLED;
}