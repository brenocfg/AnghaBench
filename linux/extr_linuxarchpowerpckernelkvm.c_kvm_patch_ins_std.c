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
typedef  long u32 ;

/* Variables and functions */
 long KVM_INST_STW ; 
 int /*<<< orphan*/  kvm_patch_ins (long*,long) ; 

__attribute__((used)) static void kvm_patch_ins_std(u32 *inst, long addr, u32 rt)
{
#ifdef CONFIG_64BIT
	kvm_patch_ins(inst, KVM_INST_STD | rt | (addr & 0x0000fffc));
#else
	kvm_patch_ins(inst, KVM_INST_STW | rt | ((addr + 4) & 0x0000fffc));
#endif
}