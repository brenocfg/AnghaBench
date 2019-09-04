#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct mpc52xx_gpt_priv {scalar_t__ ipb_freq; int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int) ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

u64 mpc52xx_gpt_timer_period(struct mpc52xx_gpt_priv *gpt)
{
	u64 period;
	u64 prescale;
	unsigned long flags;

	raw_spin_lock_irqsave(&gpt->lock, flags);
	period = in_be32(&gpt->regs->count);
	raw_spin_unlock_irqrestore(&gpt->lock, flags);

	prescale = period >> 16;
	period &= 0xffff;
	if (prescale == 0)
		prescale = 0x10000;
	period = period * prescale * 1000000000ULL;
	do_div(period, (u64)gpt->ipb_freq);
	return period;
}