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
 unsigned int MIPS_CONF3_CTXTC ; 
 unsigned int MIPS_CONF3_MSA ; 
 unsigned int MIPS_CONF3_ULRI ; 
 unsigned int MIPS_CONF_M ; 
 scalar_t__ kvm_mips_guest_can_have_msa (int /*<<< orphan*/ *) ; 
 unsigned int kvm_vz_config3_guest_wrmask (struct kvm_vcpu*) ; 

__attribute__((used)) static inline unsigned int kvm_vz_config3_user_wrmask(struct kvm_vcpu *vcpu)
{
	unsigned int mask = kvm_vz_config3_guest_wrmask(vcpu) | MIPS_CONF_M |
		MIPS_CONF3_ULRI | MIPS_CONF3_CTXTC;

	/* Permit MSA to be present if MSA is supported */
	if (kvm_mips_guest_can_have_msa(&vcpu->arch))
		mask |= MIPS_CONF3_MSA;

	return mask;
}