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
 int /*<<< orphan*/  APIC_DFR ; 
 unsigned long APIC_DFR_FLAT ; 
 int /*<<< orphan*/  APIC_LDR ; 
 int /*<<< orphan*/  apic_write (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long calculate_ldr (int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void bigsmp_init_apic_ldr(void)
{
	unsigned long val;
	int cpu = smp_processor_id();

	apic_write(APIC_DFR, APIC_DFR_FLAT);
	val = calculate_ldr(cpu);
	apic_write(APIC_LDR, val);
}