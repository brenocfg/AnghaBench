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
struct scc_channel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __scc_start_tx_timer (struct scc_channel*,void (*) (struct timer_list*),unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void scc_start_tx_timer(struct scc_channel *scc,
			       void (*handler)(struct timer_list *t),
			       unsigned long when)
{
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags);
	__scc_start_tx_timer(scc, handler, when);
	spin_unlock_irqrestore(&scc->lock, flags);
}