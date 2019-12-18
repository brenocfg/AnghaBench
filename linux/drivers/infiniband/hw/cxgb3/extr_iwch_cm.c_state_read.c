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
struct iwch_ep_common {int state; int /*<<< orphan*/  lock; } ;
typedef  enum iwch_ep_state { ____Placeholder_iwch_ep_state } iwch_ep_state ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static enum iwch_ep_state state_read(struct iwch_ep_common *epc)
{
	unsigned long flags;
	enum iwch_ep_state state;

	spin_lock_irqsave(&epc->lock, flags);
	state = epc->state;
	spin_unlock_irqrestore(&epc->lock, flags);
	return state;
}