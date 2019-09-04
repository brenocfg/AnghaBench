#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
struct thread_struct {int /*<<< orphan*/ * fp_save_area; TYPE_2__* regs; } ;
struct TYPE_5__ {int guest_owned_ext; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_7__ {struct thread_struct thread; } ;
struct TYPE_6__ {int msr; } ;

/* Variables and functions */
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  giveup_fpu (TYPE_3__*) ; 
 int /*<<< orphan*/  kvmppc_recalc_shadow_msr (struct kvm_vcpu*) ; 

void kvmppc_giveup_ext(struct kvm_vcpu *vcpu, ulong msr)
{
	struct thread_struct *t = &current->thread;

	/*
	 * VSX instructions can access FP and vector registers, so if
	 * we are giving up VSX, make sure we give up FP and VMX as well.
	 */
	if (msr & MSR_VSX)
		msr |= MSR_FP | MSR_VEC;

	msr &= vcpu->arch.guest_owned_ext;
	if (!msr)
		return;

#ifdef DEBUG_EXT
	printk(KERN_INFO "Giving up ext 0x%lx\n", msr);
#endif

	if (msr & MSR_FP) {
		/*
		 * Note that on CPUs with VSX, giveup_fpu stores
		 * both the traditional FP registers and the added VSX
		 * registers into thread.fp_state.fpr[].
		 */
		if (t->regs->msr & MSR_FP)
			giveup_fpu(current);
		t->fp_save_area = NULL;
	}

#ifdef CONFIG_ALTIVEC
	if (msr & MSR_VEC) {
		if (current->thread.regs->msr & MSR_VEC)
			giveup_altivec(current);
		t->vr_save_area = NULL;
	}
#endif

	vcpu->arch.guest_owned_ext &= ~(msr | MSR_VSX);
	kvmppc_recalc_shadow_msr(vcpu);
}