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
struct TYPE_2__ {int /*<<< orphan*/  l14_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbus_writel (unsigned int,int /*<<< orphan*/ *) ; 
 unsigned int timer_value (unsigned int) ; 
 TYPE_1__** timers_percpu ; 

__attribute__((used)) static void sun4m_load_profile_irq(int cpu, unsigned int limit)
{
	unsigned int value = limit ? timer_value(limit) : 0;
	sbus_writel(value, &timers_percpu[cpu]->l14_limit);
}