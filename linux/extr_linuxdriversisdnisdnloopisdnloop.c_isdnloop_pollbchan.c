#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_7__ {scalar_t__ expires; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  isdnloop_lock; TYPE_5__ rb_timer; } ;
typedef  TYPE_1__ isdnloop_card ;

/* Variables and functions */
 int ISDNLOOP_FLAGS_B1ACTIVE ; 
 int ISDNLOOP_FLAGS_B2ACTIVE ; 
 int ISDNLOOP_FLAGS_RBTIMER ; 
 scalar_t__ ISDNLOOP_TIMER_BCREAD ; 
 int /*<<< orphan*/  add_timer (TYPE_5__*) ; 
 TYPE_1__* card ; 
 TYPE_1__* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdnloop_bchan_send (TYPE_1__*,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  rb_timer ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
isdnloop_pollbchan(struct timer_list *t)
{
	isdnloop_card *card = from_timer(card, t, rb_timer);
	unsigned long flags;

	if (card->flags & ISDNLOOP_FLAGS_B1ACTIVE)
		isdnloop_bchan_send(card, 0);
	if (card->flags & ISDNLOOP_FLAGS_B2ACTIVE)
		isdnloop_bchan_send(card, 1);
	if (card->flags & (ISDNLOOP_FLAGS_B1ACTIVE | ISDNLOOP_FLAGS_B2ACTIVE)) {
		/* schedule b-channel polling again */
		spin_lock_irqsave(&card->isdnloop_lock, flags);
		card->rb_timer.expires = jiffies + ISDNLOOP_TIMER_BCREAD;
		add_timer(&card->rb_timer);
		card->flags |= ISDNLOOP_FLAGS_RBTIMER;
		spin_unlock_irqrestore(&card->isdnloop_lock, flags);
	} else
		card->flags &= ~ISDNLOOP_FLAGS_RBTIMER;
}