#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int IA64_THREAD_DBG_VALID ; 
 int IA64_THREAD_FPH_VALID ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ia64_drop_fpu (TYPE_2__*) ; 

void
flush_thread (void)
{
	/* drop floating-point and debug-register state if it exists: */
	current->thread.flags &= ~(IA64_THREAD_FPH_VALID | IA64_THREAD_DBG_VALID);
	ia64_drop_fpu(current);
}