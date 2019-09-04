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
struct group_irq {int /*<<< orphan*/  (* enable ) (struct group_irq*,int) ;int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  groupirq_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct group_irq*,int) ; 

__attribute__((used)) static int group_irq_enable(struct group_irq *group_irq)
{
	unsigned long flags;

	spin_lock_irqsave(&groupirq_lock, flags);
	if (group_irq->enabled++ == 0)
		(group_irq->enable)(group_irq, 1);
	spin_unlock_irqrestore(&groupirq_lock, flags);

	return 0;
}