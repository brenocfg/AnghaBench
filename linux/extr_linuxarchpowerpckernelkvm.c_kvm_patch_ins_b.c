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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int KVM_INST_B ; 
 int KVM_INST_B_MASK ; 
 int /*<<< orphan*/  kvm_patch_ins (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void kvm_patch_ins_b(u32 *inst, int addr)
{
#if defined(CONFIG_RELOCATABLE) && defined(CONFIG_PPC_BOOK3S)
	/* On relocatable kernels interrupts handlers and our code
	   can be in different regions, so we don't patch them */

	if ((ulong)inst < (ulong)&__end_interrupts)
		return;
#endif

	kvm_patch_ins(inst, KVM_INST_B | (addr & KVM_INST_B_MASK));
}