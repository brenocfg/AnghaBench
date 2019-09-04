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
typedef  int ulong ;
struct thread_struct {TYPE_1__* regs; int /*<<< orphan*/ * fp_save_area; } ;
struct TYPE_5__ {int hflags; int guest_owned_ext; int /*<<< orphan*/  fp; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_6__ {struct thread_struct thread; } ;
struct TYPE_4__ {int msr; } ;

/* Variables and functions */
 int BOOK3S_HFLAG_PAIRED_SINGLE ; 
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 int RESUME_GUEST ; 
 int /*<<< orphan*/  SRR1_PROGILL ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  disable_kernel_fp () ; 
 int /*<<< orphan*/  enable_kernel_fp () ; 
 int /*<<< orphan*/  kvmppc_book3s_queue_irqprio (struct kvm_vcpu*,unsigned int) ; 
 int /*<<< orphan*/  kvmppc_core_queue_program (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_recalc_shadow_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  load_fp_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int kvmppc_handle_ext(struct kvm_vcpu *vcpu, unsigned int exit_nr,
			     ulong msr)
{
	struct thread_struct *t = &current->thread;

	/* When we have paired singles, we emulate in software */
	if (vcpu->arch.hflags & BOOK3S_HFLAG_PAIRED_SINGLE)
		return RESUME_GUEST;

	if (!(kvmppc_get_msr(vcpu) & msr)) {
		kvmppc_book3s_queue_irqprio(vcpu, exit_nr);
		return RESUME_GUEST;
	}

	if (msr == MSR_VSX) {
		/* No VSX?  Give an illegal instruction interrupt */
#ifdef CONFIG_VSX
		if (!cpu_has_feature(CPU_FTR_VSX))
#endif
		{
			kvmppc_core_queue_program(vcpu, SRR1_PROGILL);
			return RESUME_GUEST;
		}

		/*
		 * We have to load up all the FP and VMX registers before
		 * we can let the guest use VSX instructions.
		 */
		msr = MSR_FP | MSR_VEC | MSR_VSX;
	}

	/* See if we already own all the ext(s) needed */
	msr &= ~vcpu->arch.guest_owned_ext;
	if (!msr)
		return RESUME_GUEST;

#ifdef DEBUG_EXT
	printk(KERN_INFO "Loading up ext 0x%lx\n", msr);
#endif

	if (msr & MSR_FP) {
		preempt_disable();
		enable_kernel_fp();
		load_fp_state(&vcpu->arch.fp);
		disable_kernel_fp();
		t->fp_save_area = &vcpu->arch.fp;
		preempt_enable();
	}

	if (msr & MSR_VEC) {
#ifdef CONFIG_ALTIVEC
		preempt_disable();
		enable_kernel_altivec();
		load_vr_state(&vcpu->arch.vr);
		disable_kernel_altivec();
		t->vr_save_area = &vcpu->arch.vr;
		preempt_enable();
#endif
	}

	t->regs->msr |= msr;
	vcpu->arch.guest_owned_ext |= msr;
	kvmppc_recalc_shadow_msr(vcpu);

	return RESUME_GUEST;
}