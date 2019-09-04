#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct kvm {int dummy; } ;
struct TYPE_2__ {unsigned int tss_addr; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TSS_PRIVATE_MEMSLOT ; 
 scalar_t__ enable_unrestricted_guest ; 
 int init_rmode_tss (struct kvm*) ; 
 TYPE_1__* to_kvm_vmx (struct kvm*) ; 
 int x86_set_memory_region (struct kvm*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int vmx_set_tss_addr(struct kvm *kvm, unsigned int addr)
{
	int ret;

	if (enable_unrestricted_guest)
		return 0;

	ret = x86_set_memory_region(kvm, TSS_PRIVATE_MEMSLOT, addr,
				    PAGE_SIZE * 3);
	if (ret)
		return ret;
	to_kvm_vmx(kvm)->tss_addr = addr;
	return init_rmode_tss(kvm);
}