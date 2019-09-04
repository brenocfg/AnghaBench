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
 long KVM_INST_LWZ ; 
 int /*<<< orphan*/  kvm_patch_ins (long*,long) ; 

__attribute__((used)) static void kvm_patch_ins_lwz(u32 *inst, long addr, u32 rt)
{
	kvm_patch_ins(inst, KVM_INST_LWZ | rt | (addr & 0x0000ffff));
}