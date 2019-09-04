#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_event {int dummy; } ;
struct TYPE_3__ {scalar_t__ enabled; } ;
struct TYPE_4__ {TYPE_1__ step_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_install_hw_breakpoint (struct perf_event*) ; 
 int /*<<< orphan*/  arch_uninstall_hw_breakpoint (struct perf_event*) ; 
 TYPE_2__* counter_arch_bp (struct perf_event*) ; 

__attribute__((used)) static void disable_single_step(struct perf_event *bp)
{
	arch_uninstall_hw_breakpoint(bp);
	counter_arch_bp(bp)->step_ctrl.enabled = 0;
	arch_install_hw_breakpoint(bp);
}