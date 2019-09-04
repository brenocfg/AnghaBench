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
struct sh_cmt_channel {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sh_cmt_set_next (struct sh_cmt_channel*,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sh_cmt_set_next(struct sh_cmt_channel *ch, unsigned long delta)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&ch->lock, flags);
	__sh_cmt_set_next(ch, delta);
	raw_spin_unlock_irqrestore(&ch->lock, flags);
}