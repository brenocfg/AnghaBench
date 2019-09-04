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
 unsigned int MIPS_CONF5_CV ; 
 unsigned int MIPS_CONF5_FRE ; 
 unsigned int MIPS_CONF5_K ; 
 unsigned int MIPS_CONF5_MSAEN ; 
 unsigned int MIPS_CONF5_SBRI ; 
 unsigned int MIPS_CONF5_UFE ; 
 unsigned int MIPS_CONF5_UFR ; 
 scalar_t__ cpu_has_fre ; 
 scalar_t__ cpu_has_ufr ; 
 scalar_t__ kvm_mips_guest_has_fpu (int /*<<< orphan*/ *) ; 
 scalar_t__ kvm_mips_guest_has_msa (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline unsigned int kvm_vz_config5_guest_wrmask(struct kvm_vcpu *vcpu)
{
	unsigned int mask = MIPS_CONF5_K | MIPS_CONF5_CV | MIPS_CONF5_SBRI;

	/* Permit MSAEn changes if MSA supported and enabled */
	if (kvm_mips_guest_has_msa(&vcpu->arch))
		mask |= MIPS_CONF5_MSAEN;

	/*
	 * Permit guest FPU mode changes if FPU is enabled and the relevant
	 * feature exists according to FIR register.
	 */
	if (kvm_mips_guest_has_fpu(&vcpu->arch)) {
		if (cpu_has_ufr)
			mask |= MIPS_CONF5_UFR;
		if (cpu_has_fre)
			mask |= MIPS_CONF5_FRE | MIPS_CONF5_UFE;
	}

	return mask;
}