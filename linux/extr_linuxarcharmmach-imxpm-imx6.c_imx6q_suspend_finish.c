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
struct TYPE_2__ {int /*<<< orphan*/  vbase; } ;
struct imx6_cpu_pm_info {TYPE_1__ l2_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  imx6_suspend_in_ocram_fn (scalar_t__) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 scalar_t__ suspend_ocram_base ; 

__attribute__((used)) static int imx6q_suspend_finish(unsigned long val)
{
	if (!imx6_suspend_in_ocram_fn) {
		cpu_do_idle();
	} else {
		/*
		 * call low level suspend function in ocram,
		 * as we need to float DDR IO.
		 */
		local_flush_tlb_all();
		/* check if need to flush internal L2 cache */
		if (!((struct imx6_cpu_pm_info *)
			suspend_ocram_base)->l2_base.vbase)
			flush_cache_all();
		imx6_suspend_in_ocram_fn(suspend_ocram_base);
	}

	return 0;
}