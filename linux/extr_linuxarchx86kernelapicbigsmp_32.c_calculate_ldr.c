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
 int /*<<< orphan*/  APIC_LDR ; 
 unsigned long APIC_LDR_MASK ; 
 unsigned long SET_APIC_LOGICAL_ID (unsigned long) ; 
 unsigned long apic_read (int /*<<< orphan*/ ) ; 
 unsigned long per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  x86_bios_cpu_apicid ; 

__attribute__((used)) static inline unsigned long calculate_ldr(int cpu)
{
	unsigned long val, id;

	val = apic_read(APIC_LDR) & ~APIC_LDR_MASK;
	id = per_cpu(x86_bios_cpu_apicid, cpu);
	val |= SET_APIC_LOGICAL_ID(id);

	return val;
}