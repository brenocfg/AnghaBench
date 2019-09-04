#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
struct TYPE_6__ {TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {int addr; } ;
struct TYPE_5__ {int perc; int* gcr; int /*<<< orphan*/  iprcc; TYPE_1__ gpsw; } ;

/* Variables and functions */
 int PER_CODE_BRANCH ; 
 int PER_CODE_IFETCH ; 
 int const PER_CODE_MASK ; 
 int PER_CONTROL_BRANCH_ADDRESS ; 
 int /*<<< orphan*/  PGM_PER ; 
 int /*<<< orphan*/  guest_per_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  in_addr_range (unsigned long,int,int) ; 
 int per_fetched_addr (struct kvm_vcpu*,unsigned long*) ; 

__attribute__((used)) static int filter_guest_per_event(struct kvm_vcpu *vcpu)
{
	const u8 perc = vcpu->arch.sie_block->perc;
	u64 addr = vcpu->arch.sie_block->gpsw.addr;
	u64 cr9 = vcpu->arch.sie_block->gcr[9];
	u64 cr10 = vcpu->arch.sie_block->gcr[10];
	u64 cr11 = vcpu->arch.sie_block->gcr[11];
	/* filter all events, demanded by the guest */
	u8 guest_perc = perc & (cr9 >> 24) & PER_CODE_MASK;
	unsigned long fetched_addr;
	int rc;

	if (!guest_per_enabled(vcpu))
		guest_perc = 0;

	/* filter "successful-branching" events */
	if (guest_perc & PER_CODE_BRANCH &&
	    cr9 & PER_CONTROL_BRANCH_ADDRESS &&
	    !in_addr_range(addr, cr10, cr11))
		guest_perc &= ~PER_CODE_BRANCH;

	/* filter "instruction-fetching" events */
	if (guest_perc & PER_CODE_IFETCH) {
		rc = per_fetched_addr(vcpu, &fetched_addr);
		if (rc < 0)
			return rc;
		/*
		 * Don't inject an irq on exceptions. This would make handling
		 * on icpt code 8 very complex (as PSW was already rewound).
		 */
		if (rc || !in_addr_range(fetched_addr, cr10, cr11))
			guest_perc &= ~PER_CODE_IFETCH;
	}

	/* All other PER events will be given to the guest */
	/* TODO: Check altered address/address space */

	vcpu->arch.sie_block->perc = guest_perc;

	if (!guest_perc)
		vcpu->arch.sie_block->iprcc &= ~PGM_PER;
	return 0;
}