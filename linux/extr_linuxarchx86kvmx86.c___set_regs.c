#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pending; } ;
struct TYPE_4__ {int emulate_regs_need_sync_from_vcpu; int emulate_regs_need_sync_to_vcpu; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_regs {int rflags; int /*<<< orphan*/  rip; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsp; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  VCPU_REGS_RAX ; 
 int /*<<< orphan*/  VCPU_REGS_RBP ; 
 int /*<<< orphan*/  VCPU_REGS_RBX ; 
 int /*<<< orphan*/  VCPU_REGS_RCX ; 
 int /*<<< orphan*/  VCPU_REGS_RDI ; 
 int /*<<< orphan*/  VCPU_REGS_RDX ; 
 int /*<<< orphan*/  VCPU_REGS_RSI ; 
 int /*<<< orphan*/  VCPU_REGS_RSP ; 
 int X86_EFLAGS_FIXED ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_register_write (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_rflags (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void __set_regs(struct kvm_vcpu *vcpu, struct kvm_regs *regs)
{
	vcpu->arch.emulate_regs_need_sync_from_vcpu = true;
	vcpu->arch.emulate_regs_need_sync_to_vcpu = false;

	kvm_register_write(vcpu, VCPU_REGS_RAX, regs->rax);
	kvm_register_write(vcpu, VCPU_REGS_RBX, regs->rbx);
	kvm_register_write(vcpu, VCPU_REGS_RCX, regs->rcx);
	kvm_register_write(vcpu, VCPU_REGS_RDX, regs->rdx);
	kvm_register_write(vcpu, VCPU_REGS_RSI, regs->rsi);
	kvm_register_write(vcpu, VCPU_REGS_RDI, regs->rdi);
	kvm_register_write(vcpu, VCPU_REGS_RSP, regs->rsp);
	kvm_register_write(vcpu, VCPU_REGS_RBP, regs->rbp);
#ifdef CONFIG_X86_64
	kvm_register_write(vcpu, VCPU_REGS_R8, regs->r8);
	kvm_register_write(vcpu, VCPU_REGS_R9, regs->r9);
	kvm_register_write(vcpu, VCPU_REGS_R10, regs->r10);
	kvm_register_write(vcpu, VCPU_REGS_R11, regs->r11);
	kvm_register_write(vcpu, VCPU_REGS_R12, regs->r12);
	kvm_register_write(vcpu, VCPU_REGS_R13, regs->r13);
	kvm_register_write(vcpu, VCPU_REGS_R14, regs->r14);
	kvm_register_write(vcpu, VCPU_REGS_R15, regs->r15);
#endif

	kvm_rip_write(vcpu, regs->rip);
	kvm_set_rflags(vcpu, regs->rflags | X86_EFLAGS_FIXED);

	vcpu->arch.exception.pending = false;

	kvm_make_request(KVM_REQ_EVENT, vcpu);
}