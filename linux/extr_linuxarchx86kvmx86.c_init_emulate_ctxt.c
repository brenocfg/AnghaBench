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
struct x86_emulate_ctxt {int eflags; int tf; int /*<<< orphan*/  mode; int /*<<< orphan*/  eip; } ;
struct TYPE_3__ {int emulate_regs_need_sync_from_vcpu; struct x86_emulate_ctxt emulate_ctxt; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_cs_db_l_bits ) (struct kvm_vcpu*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ HF_GUEST_MASK ; 
 scalar_t__ HF_SMM_INSIDE_NMI_MASK ; 
 scalar_t__ HF_SMM_MASK ; 
 scalar_t__ X86EMUL_GUEST_MASK ; 
 int /*<<< orphan*/  X86EMUL_MODE_PROT16 ; 
 int /*<<< orphan*/  X86EMUL_MODE_PROT32 ; 
 int /*<<< orphan*/  X86EMUL_MODE_PROT64 ; 
 int /*<<< orphan*/  X86EMUL_MODE_REAL ; 
 int /*<<< orphan*/  X86EMUL_MODE_VM86 ; 
 scalar_t__ X86EMUL_SMM_INSIDE_NMI_MASK ; 
 scalar_t__ X86EMUL_SMM_MASK ; 
 int X86_EFLAGS_TF ; 
 int X86_EFLAGS_VM ; 
 int /*<<< orphan*/  init_decode_cache (struct x86_emulate_ctxt*) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_protmode (struct kvm_vcpu*) ; 
 int kvm_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_read (struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int*,int*) ; 

__attribute__((used)) static void init_emulate_ctxt(struct kvm_vcpu *vcpu)
{
	struct x86_emulate_ctxt *ctxt = &vcpu->arch.emulate_ctxt;
	int cs_db, cs_l;

	kvm_x86_ops->get_cs_db_l_bits(vcpu, &cs_db, &cs_l);

	ctxt->eflags = kvm_get_rflags(vcpu);
	ctxt->tf = (ctxt->eflags & X86_EFLAGS_TF) != 0;

	ctxt->eip = kvm_rip_read(vcpu);
	ctxt->mode = (!is_protmode(vcpu))		? X86EMUL_MODE_REAL :
		     (ctxt->eflags & X86_EFLAGS_VM)	? X86EMUL_MODE_VM86 :
		     (cs_l && is_long_mode(vcpu))	? X86EMUL_MODE_PROT64 :
		     cs_db				? X86EMUL_MODE_PROT32 :
							  X86EMUL_MODE_PROT16;
	BUILD_BUG_ON(HF_GUEST_MASK != X86EMUL_GUEST_MASK);
	BUILD_BUG_ON(HF_SMM_MASK != X86EMUL_SMM_MASK);
	BUILD_BUG_ON(HF_SMM_INSIDE_NMI_MASK != X86EMUL_SMM_INSIDE_NMI_MASK);

	init_decode_cache(ctxt);
	vcpu->arch.emulate_regs_need_sync_from_vcpu = false;
}