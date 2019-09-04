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
struct em_sti_priv {int* active; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t USER_CLOCKEVENT ; 
 size_t USER_CLOCKSOURCE ; 
 int em_sti_enable (struct em_sti_priv*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int em_sti_start(struct em_sti_priv *p, unsigned int user)
{
	unsigned long flags;
	int used_before;
	int ret = 0;

	raw_spin_lock_irqsave(&p->lock, flags);
	used_before = p->active[USER_CLOCKSOURCE] | p->active[USER_CLOCKEVENT];
	if (!used_before)
		ret = em_sti_enable(p);

	if (!ret)
		p->active[user] = 1;
	raw_spin_unlock_irqrestore(&p->lock, flags);

	return ret;
}