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
typedef  union kvmppc_one_reg {int dummy; } kvmppc_one_reg ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  sprg9; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  KVM_REG_PPC_SPRG9 128 
 int kvmppc_set_one_reg_e500_tlb (struct kvm_vcpu*,int,union kvmppc_one_reg*) ; 
 int /*<<< orphan*/  set_reg_val (int,union kvmppc_one_reg) ; 

__attribute__((used)) static int kvmppc_set_one_reg_e500mc(struct kvm_vcpu *vcpu, u64 id,
			      union kvmppc_one_reg *val)
{
	int r = 0;

	switch (id) {
	case KVM_REG_PPC_SPRG9:
		vcpu->arch.sprg9 = set_reg_val(id, *val);
		break;
	default:
		r = kvmppc_set_one_reg_e500_tlb(vcpu, id, val);
	}

	return r;
}