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
struct TYPE_2__ {scalar_t__ slb_cache_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __slb_flush_and_rebolt () ; 
 TYPE_1__* get_paca () ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  irqs_disabled () ; 

void slb_flush_and_rebolt(void)
{

	WARN_ON(!irqs_disabled());

	/*
	 * We can't take a PMU exception in the following code, so hard
	 * disable interrupts.
	 */
	hard_irq_disable();

	__slb_flush_and_rebolt();
	get_paca()->slb_cache_ptr = 0;
}