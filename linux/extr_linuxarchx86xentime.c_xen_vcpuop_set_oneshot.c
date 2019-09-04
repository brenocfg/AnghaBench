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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPUOP_stop_periodic_timer ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  xen_vcpu_nr (int) ; 

__attribute__((used)) static int xen_vcpuop_set_oneshot(struct clock_event_device *evt)
{
	int cpu = smp_processor_id();

	if (HYPERVISOR_vcpu_op(VCPUOP_stop_periodic_timer, xen_vcpu_nr(cpu),
			       NULL))
		BUG();

	return 0;
}