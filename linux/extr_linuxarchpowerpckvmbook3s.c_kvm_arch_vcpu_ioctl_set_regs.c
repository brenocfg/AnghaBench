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
struct kvm_regs {int /*<<< orphan*/ * gpr; int /*<<< orphan*/  sprg7; int /*<<< orphan*/  sprg6; int /*<<< orphan*/  sprg5; int /*<<< orphan*/  sprg4; int /*<<< orphan*/  sprg3; int /*<<< orphan*/  sprg2; int /*<<< orphan*/  sprg1; int /*<<< orphan*/  sprg0; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  msr; int /*<<< orphan*/  xer; int /*<<< orphan*/  lr; int /*<<< orphan*/  ctr; int /*<<< orphan*/  cr; int /*<<< orphan*/  pc; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_set_cr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_ctr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_gpr (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_lr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_pc (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg0 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg2 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg3 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg4 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg5 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg6 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_sprg7 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_srr0 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_srr1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_xer (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvm_arch_vcpu_ioctl_set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
{
	int i;

	kvmppc_set_pc(vcpu, regs->pc);
	kvmppc_set_cr(vcpu, regs->cr);
	kvmppc_set_ctr(vcpu, regs->ctr);
	kvmppc_set_lr(vcpu, regs->lr);
	kvmppc_set_xer(vcpu, regs->xer);
	kvmppc_set_msr(vcpu, regs->msr);
	kvmppc_set_srr0(vcpu, regs->srr0);
	kvmppc_set_srr1(vcpu, regs->srr1);
	kvmppc_set_sprg0(vcpu, regs->sprg0);
	kvmppc_set_sprg1(vcpu, regs->sprg1);
	kvmppc_set_sprg2(vcpu, regs->sprg2);
	kvmppc_set_sprg3(vcpu, regs->sprg3);
	kvmppc_set_sprg4(vcpu, regs->sprg4);
	kvmppc_set_sprg5(vcpu, regs->sprg5);
	kvmppc_set_sprg6(vcpu, regs->sprg6);
	kvmppc_set_sprg7(vcpu, regs->sprg7);

	for (i = 0; i < ARRAY_SIZE(regs->gpr); i++)
		kvmppc_set_gpr(vcpu, i, regs->gpr[i]);

	return 0;
}