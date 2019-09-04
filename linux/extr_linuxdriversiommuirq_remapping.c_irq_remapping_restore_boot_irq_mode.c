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
 int /*<<< orphan*/  X86_FEATURE_APIC ; 
 scalar_t__ apic_from_smp_config () ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disconnect_bsp_APIC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void irq_remapping_restore_boot_irq_mode(void)
{
	/*
	 * With interrupt-remapping, for now we will use virtual wire A
	 * mode, as virtual wire B is little complex (need to configure
	 * both IOAPIC RTE as well as interrupt-remapping table entry).
	 * As this gets called during crash dump, keep this simple for
	 * now.
	 */
	if (boot_cpu_has(X86_FEATURE_APIC) || apic_from_smp_config())
		disconnect_bsp_APIC(0);
}