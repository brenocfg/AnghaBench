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
union mips_instruction {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int kvm_mips_trans_replace (struct kvm_vcpu*,int /*<<< orphan*/ *,union mips_instruction) ; 

int kvm_mips_trans_cache_index(union mips_instruction inst, u32 *opc,
			       struct kvm_vcpu *vcpu)
{
	union mips_instruction nop_inst = { 0 };

	/* Replace the CACHE instruction, with a NOP */
	return kvm_mips_trans_replace(vcpu, opc, nop_inst);
}