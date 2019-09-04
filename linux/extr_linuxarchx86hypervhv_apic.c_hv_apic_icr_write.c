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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_ICR ; 
 int SET_APIC_DEST_FIELD (int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hv_apic_icr_write(u32 low, u32 id)
{
	u64 reg_val;

	reg_val = SET_APIC_DEST_FIELD(id);
	reg_val = reg_val << 32;
	reg_val |= low;

	wrmsrl(HV_X64_MSR_ICR, reg_val);
}