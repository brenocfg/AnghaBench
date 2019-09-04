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
struct coproc_reg {int Op1; int CRn; int Op2; int CRm; scalar_t__ is_64bit; } ;

/* Variables and functions */
 int KVM_REG_ARM ; 
 int KVM_REG_ARM_32_CRN_SHIFT ; 
 int KVM_REG_ARM_32_OPC2_SHIFT ; 
 int KVM_REG_ARM_COPROC_SHIFT ; 
 int KVM_REG_ARM_CRM_SHIFT ; 
 int KVM_REG_ARM_OPC1_SHIFT ; 
 int KVM_REG_SIZE_U32 ; 
 int KVM_REG_SIZE_U64 ; 

__attribute__((used)) static u64 cp15_to_index(const struct coproc_reg *reg)
{
	u64 val = KVM_REG_ARM | (15 << KVM_REG_ARM_COPROC_SHIFT);
	if (reg->is_64bit) {
		val |= KVM_REG_SIZE_U64;
		val |= (reg->Op1 << KVM_REG_ARM_OPC1_SHIFT);
		/*
		 * CRn always denotes the primary coproc. reg. nr. for the
		 * in-kernel representation, but the user space API uses the
		 * CRm for the encoding, because it is modelled after the
		 * MRRC/MCRR instructions: see the ARM ARM rev. c page
		 * B3-1445
		 */
		val |= (reg->CRn << KVM_REG_ARM_CRM_SHIFT);
	} else {
		val |= KVM_REG_SIZE_U32;
		val |= (reg->Op1 << KVM_REG_ARM_OPC1_SHIFT);
		val |= (reg->Op2 << KVM_REG_ARM_32_OPC2_SHIFT);
		val |= (reg->CRm << KVM_REG_ARM_CRM_SHIFT);
		val |= (reg->CRn << KVM_REG_ARM_32_CRN_SHIFT);
	}
	return val;
}