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
struct kvmppc_mmu {int /*<<< orphan*/  is_dcbz32; int /*<<< orphan*/  ea_to_vp; int /*<<< orphan*/  esid_to_vsid; int /*<<< orphan*/  tlbie; int /*<<< orphan*/  reset_msr; int /*<<< orphan*/  xlate; int /*<<< orphan*/  slbia; int /*<<< orphan*/  slbie; int /*<<< orphan*/  slbmfev; int /*<<< orphan*/  slbmfee; int /*<<< orphan*/  slbmte; int /*<<< orphan*/  mtsrin; int /*<<< orphan*/ * mfsrin; } ;
struct TYPE_2__ {int /*<<< orphan*/  hflags; struct kvmppc_mmu mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_HFLAG_SLB ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_ea_to_vp ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_esid_to_vsid ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_is_dcbz32 ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_mtsrin ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_reset_msr ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbia ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbie ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbmfee ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbmfev ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_slbmte ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_tlbie ; 
 int /*<<< orphan*/  kvmppc_mmu_book3s_64_xlate ; 

void kvmppc_mmu_book3s_64_init(struct kvm_vcpu *vcpu)
{
	struct kvmppc_mmu *mmu = &vcpu->arch.mmu;

	mmu->mfsrin = NULL;
	mmu->mtsrin = kvmppc_mmu_book3s_64_mtsrin;
	mmu->slbmte = kvmppc_mmu_book3s_64_slbmte;
	mmu->slbmfee = kvmppc_mmu_book3s_64_slbmfee;
	mmu->slbmfev = kvmppc_mmu_book3s_64_slbmfev;
	mmu->slbie = kvmppc_mmu_book3s_64_slbie;
	mmu->slbia = kvmppc_mmu_book3s_64_slbia;
	mmu->xlate = kvmppc_mmu_book3s_64_xlate;
	mmu->reset_msr = kvmppc_mmu_book3s_64_reset_msr;
	mmu->tlbie = kvmppc_mmu_book3s_64_tlbie;
	mmu->esid_to_vsid = kvmppc_mmu_book3s_64_esid_to_vsid;
	mmu->ea_to_vp = kvmppc_mmu_book3s_64_ea_to_vp;
	mmu->is_dcbz32 = kvmppc_mmu_book3s_64_is_dcbz32;

	vcpu->arch.hflags |= BOOK3S_HFLAG_SLB;
}