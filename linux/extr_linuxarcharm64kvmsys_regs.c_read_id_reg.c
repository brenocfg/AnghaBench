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
typedef  scalar_t__ u32 ;
struct sys_reg_desc {scalar_t__ Op2; scalar_t__ CRm; scalar_t__ CRn; scalar_t__ Op1; scalar_t__ Op0; } ;

/* Variables and functions */
 int ID_AA64MMFR1_LOR_SHIFT ; 
 int ID_AA64PFR0_SVE_SHIFT ; 
 scalar_t__ SYS_ID_AA64MMFR1_EL1 ; 
 scalar_t__ SYS_ID_AA64PFR0_EL1 ; 
 int /*<<< orphan*/  kvm_debug (char*) ; 
 int read_sanitised_ftr_reg (scalar_t__) ; 
 scalar_t__ sys_reg (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static u64 read_id_reg(struct sys_reg_desc const *r, bool raz)
{
	u32 id = sys_reg((u32)r->Op0, (u32)r->Op1,
			 (u32)r->CRn, (u32)r->CRm, (u32)r->Op2);
	u64 val = raz ? 0 : read_sanitised_ftr_reg(id);

	if (id == SYS_ID_AA64PFR0_EL1) {
		if (val & (0xfUL << ID_AA64PFR0_SVE_SHIFT))
			kvm_debug("SVE unsupported for guests, suppressing\n");

		val &= ~(0xfUL << ID_AA64PFR0_SVE_SHIFT);
	} else if (id == SYS_ID_AA64MMFR1_EL1) {
		if (val & (0xfUL << ID_AA64MMFR1_LOR_SHIFT))
			kvm_debug("LORegions unsupported for guests, suppressing\n");

		val &= ~(0xfUL << ID_AA64MMFR1_LOR_SHIFT);
	}

	return val;
}