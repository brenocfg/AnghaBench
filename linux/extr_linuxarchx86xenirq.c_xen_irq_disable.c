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
struct TYPE_2__ {int evtchn_upcall_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable_no_resched () ; 
 TYPE_1__* this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_vcpu ; 

void xen_irq_disable(void)
{
	/* There's a one instruction preempt window here.  We need to
	   make sure we're don't switch CPUs between getting the vcpu
	   pointer and updating the mask. */
	preempt_disable();
	this_cpu_read(xen_vcpu)->evtchn_upcall_mask = 1;
	preempt_enable_no_resched();
}