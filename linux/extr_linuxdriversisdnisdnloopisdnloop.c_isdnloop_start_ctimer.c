#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  isdnloop_lock; TYPE_2__* c_timer; } ;
typedef  TYPE_1__ isdnloop_card ;
struct TYPE_6__ {scalar_t__ expires; } ;

/* Variables and functions */
 scalar_t__ ISDNLOOP_TIMER_ALERTWAIT ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  isdnloop_atimeout0 ; 
 int /*<<< orphan*/  isdnloop_atimeout1 ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdnloop_start_ctimer(isdnloop_card *card, int ch)
{
	unsigned long flags;

	spin_lock_irqsave(&card->isdnloop_lock, flags);
	timer_setup(&card->c_timer[ch], ch ? isdnloop_atimeout1
					   : isdnloop_atimeout0, 0);
	card->c_timer[ch].expires = jiffies + ISDNLOOP_TIMER_ALERTWAIT;
	add_timer(&card->c_timer[ch]);
	spin_unlock_irqrestore(&card->isdnloop_lock, flags);
}