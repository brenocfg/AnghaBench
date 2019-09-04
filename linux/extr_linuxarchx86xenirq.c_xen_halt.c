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

/* Variables and functions */
 int /*<<< orphan*/  HYPERVISOR_vcpu_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPUOP_down ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  xen_safe_halt () ; 
 int /*<<< orphan*/  xen_vcpu_nr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_halt(void)
{
	if (irqs_disabled())
		HYPERVISOR_vcpu_op(VCPUOP_down,
				   xen_vcpu_nr(smp_processor_id()), NULL);
	else
		xen_safe_halt();
}