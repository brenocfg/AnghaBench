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
struct TYPE_2__ {int /*<<< orphan*/  tclr; int /*<<< orphan*/  tier; int /*<<< orphan*/  tsicr; int /*<<< orphan*/  tmar; int /*<<< orphan*/  tldr; int /*<<< orphan*/  tcrr; int /*<<< orphan*/  twer; } ;
struct omap_dm_timer {TYPE_1__ context; int /*<<< orphan*/  irq_ena; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_TIMER_COUNTER_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_IF_CTRL_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_LOAD_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_MATCH_REG ; 
 int /*<<< orphan*/  OMAP_TIMER_WAKEUP_EN_REG ; 
 int /*<<< orphan*/  omap_dm_timer_write_reg (struct omap_dm_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_timer_restore_context(struct omap_dm_timer *timer)
{
	omap_dm_timer_write_reg(timer, OMAP_TIMER_WAKEUP_EN_REG,
				timer->context.twer);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_COUNTER_REG,
				timer->context.tcrr);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_LOAD_REG,
				timer->context.tldr);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_MATCH_REG,
				timer->context.tmar);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_IF_CTRL_REG,
				timer->context.tsicr);
	writel_relaxed(timer->context.tier, timer->irq_ena);
	omap_dm_timer_write_reg(timer, OMAP_TIMER_CTRL_REG,
				timer->context.tclr);
}