#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nr_hw_bp; struct kvm_hw_bp_info_arch* hw_bp_info; } ;
struct TYPE_3__ {TYPE_2__ guestdbg; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_hw_bp_info_arch {unsigned long addr; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_of_range (struct kvm_hw_bp_info_arch*) ; 
 scalar_t__ in_addr_range (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kvm_hw_bp_info_arch *find_hw_bp(struct kvm_vcpu *vcpu,
					      unsigned long addr)
{
	struct kvm_hw_bp_info_arch *bp_info = vcpu->arch.guestdbg.hw_bp_info;
	int i;

	if (vcpu->arch.guestdbg.nr_hw_bp == 0)
		return NULL;

	for (i = 0; i < vcpu->arch.guestdbg.nr_hw_bp; i++) {
		/* addr is directly the start or in the range of a bp */
		if (addr == bp_info->addr)
			goto found;
		if (bp_info->len > 0 &&
		    in_addr_range(addr, bp_info->addr, end_of_range(bp_info)))
			goto found;

		bp_info++;
	}

	return NULL;
found:
	return bp_info;
}