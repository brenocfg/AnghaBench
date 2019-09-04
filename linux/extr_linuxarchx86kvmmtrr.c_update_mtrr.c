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
typedef  int u32 ;
struct kvm_mtrr {int /*<<< orphan*/ * var_ranges; } ;
struct TYPE_2__ {struct kvm_mtrr mtrr_state; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_1__ arch; } ;
typedef  int gfn_t ;

/* Variables and functions */
 int MSR_IA32_CR_PAT ; 
 int MSR_MTRRdefType ; 
 scalar_t__ fixed_msr_to_range (int,int*,int*) ; 
 int /*<<< orphan*/  fixed_mtrr_is_enabled (struct kvm_mtrr*) ; 
 int /*<<< orphan*/  gpa_to_gfn (int) ; 
 int /*<<< orphan*/  kvm_arch_has_noncoherent_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_zap_gfn_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_is_enabled (struct kvm_mtrr*) ; 
 int /*<<< orphan*/  tdp_enabled ; 
 int /*<<< orphan*/  var_mtrr_range (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static void update_mtrr(struct kvm_vcpu *vcpu, u32 msr)
{
	struct kvm_mtrr *mtrr_state = &vcpu->arch.mtrr_state;
	gfn_t start, end;
	int index;

	if (msr == MSR_IA32_CR_PAT || !tdp_enabled ||
	      !kvm_arch_has_noncoherent_dma(vcpu->kvm))
		return;

	if (!mtrr_is_enabled(mtrr_state) && msr != MSR_MTRRdefType)
		return;

	/* fixed MTRRs. */
	if (fixed_msr_to_range(msr, &start, &end)) {
		if (!fixed_mtrr_is_enabled(mtrr_state))
			return;
	} else if (msr == MSR_MTRRdefType) {
		start = 0x0;
		end = ~0ULL;
	} else {
		/* variable range MTRRs. */
		index = (msr - 0x200) / 2;
		var_mtrr_range(&mtrr_state->var_ranges[index], &start, &end);
	}

	kvm_zap_gfn_range(vcpu->kvm, gpa_to_gfn(start), gpa_to_gfn(end));
}