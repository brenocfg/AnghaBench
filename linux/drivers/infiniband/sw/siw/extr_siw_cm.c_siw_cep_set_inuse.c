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
struct siw_cep {int in_use; int /*<<< orphan*/  lock; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  flush_signals (int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void siw_cep_set_inuse(struct siw_cep *cep)
{
	unsigned long flags;
retry:
	spin_lock_irqsave(&cep->lock, flags);

	if (cep->in_use) {
		spin_unlock_irqrestore(&cep->lock, flags);
		wait_event_interruptible(cep->waitq, !cep->in_use);
		if (signal_pending(current))
			flush_signals(current);
		goto retry;
	} else {
		cep->in_use = 1;
		spin_unlock_irqrestore(&cep->lock, flags);
	}
}