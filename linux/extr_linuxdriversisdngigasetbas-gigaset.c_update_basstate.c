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
struct bas_cardstate {int basstate; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int update_basstate(struct bas_cardstate *ucs,
				  int set, int clear)
{
	unsigned long flags;
	int state;

	spin_lock_irqsave(&ucs->lock, flags);
	state = ucs->basstate;
	ucs->basstate = (state & ~clear) | set;
	spin_unlock_irqrestore(&ucs->lock, flags);
	return state;
}