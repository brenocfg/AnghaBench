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
struct rt_timer {int timer_freq; int timer_div; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TIMER_REG_TMR0LOAD ; 
 int /*<<< orphan*/  TIMER_REG_TMRSTAT ; 
 int TMRSTAT_TMR0INT ; 
 int /*<<< orphan*/  rt_timer_w32 (struct rt_timer*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t rt_timer_irq(int irq, void *_rt)
{
	struct rt_timer *rt =  (struct rt_timer *) _rt;

	rt_timer_w32(rt, TIMER_REG_TMR0LOAD, rt->timer_freq / rt->timer_div);
	rt_timer_w32(rt, TIMER_REG_TMRSTAT, TMRSTAT_TMR0INT);

	return IRQ_HANDLED;
}