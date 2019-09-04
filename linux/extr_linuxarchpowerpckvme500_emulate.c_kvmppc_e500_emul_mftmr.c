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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int EMULATE_DONE ; 
 int EMULATE_FAIL ; 
 scalar_t__ TMRN_TMCFG0 ; 
 int TMRN_TMCFG0_NATHRD_SHIFT ; 
 scalar_t__ get_tmrn (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int) ; 

__attribute__((used)) static int kvmppc_e500_emul_mftmr(struct kvm_vcpu *vcpu, unsigned int inst,
				  int rt)
{
	/* Expose one thread per vcpu */
	if (get_tmrn(inst) == TMRN_TMCFG0) {
		kvmppc_set_gpr(vcpu, rt,
			       1 | (1 << TMRN_TMCFG0_NATHRD_SHIFT));
		return EMULATE_DONE;
	}

	return EMULATE_FAIL;
}