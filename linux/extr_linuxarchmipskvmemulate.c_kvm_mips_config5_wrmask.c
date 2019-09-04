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
struct kvm_vcpu {int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 unsigned int MIPS_CONF5_FRE ; 
 unsigned int MIPS_CONF5_MSAEN ; 
 scalar_t__ cpu_has_fre ; 
 scalar_t__ kvm_mips_guest_has_fpu (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_mips_guest_has_msa (int /*<<< orphan*/ *) ; 

unsigned int kvm_mips_config5_wrmask(struct kvm_vcpu *vcpu)
{
	unsigned int mask = 0;

	/* Permit MSAEn changes if MSA supported and enabled */
	if (kvm_mips_guest_has_msa(&vcpu->arch))
		mask |= MIPS_CONF5_MSAEN;

	/*
	 * Permit guest FPU mode changes if FPU is enabled and the relevant
	 * feature exists according to FIR register.
	 */
	if (kvm_mips_guest_has_fpu(&vcpu->arch)) {
		if (cpu_has_fre)
			mask |= MIPS_CONF5_FRE;
		/* We don't support UFR or UFE */
	}

	return mask;
}