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
typedef  int u32 ;

/* Variables and functions */
#define  APIC_EOI 129 
#define  APIC_TASKPRI 128 
 int /*<<< orphan*/  HV_X64_MSR_EOI ; 
 int /*<<< orphan*/  HV_X64_MSR_TPR ; 
 int native_apic_mem_read (int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 hv_apic_read(u32 reg)
{
	u32 reg_val, hi;

	switch (reg) {
	case APIC_EOI:
		rdmsr(HV_X64_MSR_EOI, reg_val, hi);
		return reg_val;
	case APIC_TASKPRI:
		rdmsr(HV_X64_MSR_TPR, reg_val, hi);
		return reg_val;

	default:
		return native_apic_mem_read(reg);
	}
}