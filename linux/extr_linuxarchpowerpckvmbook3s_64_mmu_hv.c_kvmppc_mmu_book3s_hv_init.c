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
struct kvmppc_mmu {int /*<<< orphan*/  reset_msr; int /*<<< orphan*/  xlate; } ;
struct TYPE_2__ {int slb_nr; int /*<<< orphan*/  hflags; struct kvmppc_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_HFLAG_SLB ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_hv_reset_msr ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_hv_xlate ; 

void kvmppc_mmu_book3s_hv_init(struct kvm_vcpu *vcpu)
{
	struct kvmppc_mmu *mmu = &vcpu->arch.mmu;

	vcpu->arch.slb_nr = 32;		/* POWER7/POWER8 */

	mmu->xlate = kvmppc_mmu_book3s_64_hv_xlate;
	mmu->reset_msr = kvmppc_mmu_book3s_64_hv_reset_msr;

	vcpu->arch.hflags |= BOOK3S_HFLAG_SLB;
}