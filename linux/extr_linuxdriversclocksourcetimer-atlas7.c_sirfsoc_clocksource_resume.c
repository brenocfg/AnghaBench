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
struct clocksource {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ SIRFSOC_TIMER_64COUNTER_CTRL ; 
 scalar_t__ SIRFSOC_TIMER_64COUNTER_LOAD_HI ; 
 scalar_t__ SIRFSOC_TIMER_64COUNTER_LOAD_LO ; 
 int SIRFSOC_TIMER_REG_CNT ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ sirfsoc_timer_base ; 
 scalar_t__* sirfsoc_timer_reg_list ; 
 int* sirfsoc_timer_reg_val ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void sirfsoc_clocksource_resume(struct clocksource *cs)
{
	int i;

	for (i = 0; i < SIRFSOC_TIMER_REG_CNT - 2; i++)
		writel_relaxed(sirfsoc_timer_reg_val[i], sirfsoc_timer_base + sirfsoc_timer_reg_list[i]);

	writel_relaxed(sirfsoc_timer_reg_val[SIRFSOC_TIMER_REG_CNT - 2],
		sirfsoc_timer_base + SIRFSOC_TIMER_64COUNTER_LOAD_LO);
	writel_relaxed(sirfsoc_timer_reg_val[SIRFSOC_TIMER_REG_CNT - 1],
		sirfsoc_timer_base + SIRFSOC_TIMER_64COUNTER_LOAD_HI);

	writel_relaxed(readl_relaxed(sirfsoc_timer_base + SIRFSOC_TIMER_64COUNTER_CTRL) |
		BIT(1) | BIT(0), sirfsoc_timer_base + SIRFSOC_TIMER_64COUNTER_CTRL);
}