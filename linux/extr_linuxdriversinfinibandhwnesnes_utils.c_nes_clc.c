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
struct timer_list {int dummy; } ;
struct TYPE_2__ {scalar_t__ expires; } ;
struct nes_adapter {TYPE_1__ lc_timer; int /*<<< orphan*/  phy_lock; scalar_t__* link_interrupt_count; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 struct nes_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lc_timer ; 
 struct nes_adapter* nesadapter ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void nes_clc(struct timer_list *t)
{
	struct nes_adapter *nesadapter = from_timer(nesadapter, t, lc_timer);
	unsigned long flags;

	spin_lock_irqsave(&nesadapter->phy_lock, flags);
	nesadapter->link_interrupt_count[0] = 0;
	nesadapter->link_interrupt_count[1] = 0;
	nesadapter->link_interrupt_count[2] = 0;
	nesadapter->link_interrupt_count[3] = 0;
	spin_unlock_irqrestore(&nesadapter->phy_lock, flags);

	nesadapter->lc_timer.expires = jiffies + 3600 * HZ;  /* 1 hour */
	add_timer(&nesadapter->lc_timer);
}