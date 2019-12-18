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
struct send_context {int flags; int /*<<< orphan*/  halt_wait; int /*<<< orphan*/  alloc_lock; } ;

/* Variables and functions */
 int SCF_ENABLED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void sc_stop(struct send_context *sc, int flag)
{
	unsigned long flags;

	/* stop buffer allocations */
	spin_lock_irqsave(&sc->alloc_lock, flags);
	/* mark the context */
	sc->flags |= flag;
	sc->flags &= ~SCF_ENABLED;
	spin_unlock_irqrestore(&sc->alloc_lock, flags);
	wake_up(&sc->halt_wait);
}