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
struct vcpu_info {scalar_t__ evtchn_upcall_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 struct vcpu_info* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  xed_nesting_count ; 
 int /*<<< orphan*/  xen_evtchn_handle_events (int) ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static void __xen_evtchn_do_upcall(void)
{
	struct vcpu_info *vcpu_info = __this_cpu_read(xen_vcpu);
	int cpu = get_cpu();
	unsigned count;

	do {
		vcpu_info->evtchn_upcall_pending = 0;

		if (__this_cpu_inc_return(xed_nesting_count) - 1)
			goto out;

		xen_evtchn_handle_events(cpu);

		BUG_ON(!irqs_disabled());

		count = __this_cpu_read(xed_nesting_count);
		__this_cpu_write(xed_nesting_count, 0);
	} while (count != 1 || vcpu_info->evtchn_upcall_pending);

out:

	put_cpu();
}