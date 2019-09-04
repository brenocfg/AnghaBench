#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  link; int /*<<< orphan*/  ctr; int /*<<< orphan*/  nip; } ;
struct TYPE_6__ {int /*<<< orphan*/  pid; TYPE_2__* shared; TYPE_1__ regs; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_regs {int /*<<< orphan*/ * gpr; int /*<<< orphan*/  sprg7; int /*<<< orphan*/  sprg6; int /*<<< orphan*/  sprg5; int /*<<< orphan*/  sprg4; int /*<<< orphan*/  sprg3; int /*<<< orphan*/  sprg2; int /*<<< orphan*/  sprg1; int /*<<< orphan*/  sprg0; int /*<<< orphan*/  pid; int /*<<< orphan*/  srr1; int /*<<< orphan*/  srr0; int /*<<< orphan*/  msr; int /*<<< orphan*/  xer; int /*<<< orphan*/  lr; int /*<<< orphan*/  ctr; int /*<<< orphan*/  cr; int /*<<< orphan*/  pc; } ;
struct TYPE_5__ {int /*<<< orphan*/  msr; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_get_cr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_gpr (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_get_sprg0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg2 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg4 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg5 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg6 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_sprg7 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_srr0 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_srr1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_xer (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_get_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
{
	int i;

	vcpu_load(vcpu);

	regs->pc = vcpu->arch.regs.nip;
	regs->cr = kvmppc_get_cr(vcpu);
	regs->ctr = vcpu->arch.regs.ctr;
	regs->lr = vcpu->arch.regs.link;
	regs->xer = kvmppc_get_xer(vcpu);
	regs->msr = vcpu->arch.shared->msr;
	regs->srr0 = kvmppc_get_srr0(vcpu);
	regs->srr1 = kvmppc_get_srr1(vcpu);
	regs->pid = vcpu->arch.pid;
	regs->sprg0 = kvmppc_get_sprg0(vcpu);
	regs->sprg1 = kvmppc_get_sprg1(vcpu);
	regs->sprg2 = kvmppc_get_sprg2(vcpu);
	regs->sprg3 = kvmppc_get_sprg3(vcpu);
	regs->sprg4 = kvmppc_get_sprg4(vcpu);
	regs->sprg5 = kvmppc_get_sprg5(vcpu);
	regs->sprg6 = kvmppc_get_sprg6(vcpu);
	regs->sprg7 = kvmppc_get_sprg7(vcpu);

	for (i = 0; i < ARRAY_SIZE(regs->gpr); i++)
		regs->gpr[i] = kvmppc_get_gpr(vcpu, i);

	vcpu_put(vcpu);
	return 0;
}