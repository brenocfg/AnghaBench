#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_7__ {int nr_hw_bp; TYPE_2__* hw_bp_info; } ;
struct TYPE_8__ {TYPE_3__ guestdbg; TYPE_1__* sie_block; } ;
struct kvm_vcpu {TYPE_4__ arch; } ;
struct TYPE_6__ {unsigned long addr; unsigned long len; } ;
struct TYPE_5__ {int* gcr; } ;

/* Variables and functions */
 unsigned long MAX_INST_SIZE ; 
 int PER_CONTROL_BRANCH_ADDRESS ; 
 int PER_EVENT_BRANCH ; 
 int PER_EVENT_IFETCH ; 
 int /*<<< orphan*/  extend_address_range (int*,int*,unsigned long,unsigned long) ; 

__attribute__((used)) static void enable_all_hw_bp(struct kvm_vcpu *vcpu)
{
	unsigned long start, len;
	u64 *cr9 = &vcpu->arch.sie_block->gcr[9];
	u64 *cr10 = &vcpu->arch.sie_block->gcr[10];
	u64 *cr11 = &vcpu->arch.sie_block->gcr[11];
	int i;

	if (vcpu->arch.guestdbg.nr_hw_bp <= 0 ||
	    vcpu->arch.guestdbg.hw_bp_info == NULL)
		return;

	/*
	 * If the guest is not interested in branching events, we can safely
	 * limit them to the PER address range.
	 */
	if (!(*cr9 & PER_EVENT_BRANCH))
		*cr9 |= PER_CONTROL_BRANCH_ADDRESS;
	*cr9 |= PER_EVENT_IFETCH | PER_EVENT_BRANCH;

	for (i = 0; i < vcpu->arch.guestdbg.nr_hw_bp; i++) {
		start = vcpu->arch.guestdbg.hw_bp_info[i].addr;
		len = vcpu->arch.guestdbg.hw_bp_info[i].len;

		/*
		 * The instruction in front of the desired bp has to
		 * report instruction-fetching events
		 */
		if (start < MAX_INST_SIZE) {
			len += start;
			start = 0;
		} else {
			start -= MAX_INST_SIZE;
			len += MAX_INST_SIZE;
		}

		extend_address_range(cr10, cr11, start, len);
	}
}