#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tp_value; } ;
struct TYPE_5__ {TYPE_1__ uw; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 TYPE_3__* current ; 
 scalar_t__ is_compat_task () ; 
 int /*<<< orphan*/  tpidr_el0 ; 
 int /*<<< orphan*/  tpidrro_el0 ; 
 int /*<<< orphan*/  write_sysreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tls_thread_flush(void)
{
	write_sysreg(0, tpidr_el0);

	if (is_compat_task()) {
		current->thread.uw.tp_value = 0;

		/*
		 * We need to ensure ordering between the shadow state and the
		 * hardware state, so that we don't corrupt the hardware state
		 * with a stale shadow state during context switch.
		 */
		barrier();
		write_sysreg(0, tpidrro_el0);
	}
}