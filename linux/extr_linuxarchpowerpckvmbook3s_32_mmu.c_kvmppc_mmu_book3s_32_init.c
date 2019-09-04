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
struct kvmppc_mmu {int /*<<< orphan*/ * slbia; int /*<<< orphan*/ * slbie; int /*<<< orphan*/ * slbmfev; int /*<<< orphan*/ * slbmfee; int /*<<< orphan*/ * slbmte; int /*<<< orphan*/  is_dcbz32; int /*<<< orphan*/  ea_to_vp; int /*<<< orphan*/  esid_to_vsid; int /*<<< orphan*/  tlbie; int /*<<< orphan*/  reset_msr; int /*<<< orphan*/  xlate; int /*<<< orphan*/  mfsrin; int /*<<< orphan*/  mtsrin; } ;
struct TYPE_2__ {struct kvmppc_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_ea_to_vp ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_esid_to_vsid ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_is_dcbz32 ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_mfsrin ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_mtsrin ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_reset_msr ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_tlbie ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_32_xlate ; 

void kvmppc_mmu_book3s_32_init(struct kvm_vcpu *vcpu)
{
	struct kvmppc_mmu *mmu = &vcpu->arch.mmu;

	mmu->mtsrin = kvmppc_mmu_book3s_32_mtsrin;
	mmu->mfsrin = kvmppc_mmu_book3s_32_mfsrin;
	mmu->xlate = kvmppc_mmu_book3s_32_xlate;
	mmu->reset_msr = kvmppc_mmu_book3s_32_reset_msr;
	mmu->tlbie = kvmppc_mmu_book3s_32_tlbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_32_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_32_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_32_is_dcbz32;

	mmu->slbmte = NULL;
	mmu->slbmfee = NULL;
	mmu->slbmfev = NULL;
	mmu->slbie = NULL;
	mmu->slbia = NULL;
}