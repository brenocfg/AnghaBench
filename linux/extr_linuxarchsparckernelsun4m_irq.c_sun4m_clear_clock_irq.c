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
struct TYPE_2__ {int /*<<< orphan*/  l10_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbus_readl (int /*<<< orphan*/ *) ; 
 TYPE_1__* timers_global ; 

__attribute__((used)) static void sun4m_clear_clock_irq(void)
{
	sbus_readl(&timers_global->l10_limit);
}