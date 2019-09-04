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
struct vmcb_seg {int attrib; int /*<<< orphan*/  selector; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_segment {int type; int s; int dpl; int present; int avl; int l; int db; int g; int /*<<< orphan*/  unusable; int /*<<< orphan*/  selector; int /*<<< orphan*/  limit; int /*<<< orphan*/  base; } ;
struct TYPE_3__ {int cpl; } ;
struct TYPE_4__ {TYPE_1__ save; } ;

/* Variables and functions */
 int SVM_SELECTOR_AVL_SHIFT ; 
 int SVM_SELECTOR_DB_SHIFT ; 
 int SVM_SELECTOR_DPL_SHIFT ; 
 int SVM_SELECTOR_G_SHIFT ; 
 int SVM_SELECTOR_L_SHIFT ; 
 int SVM_SELECTOR_P_SHIFT ; 
 int SVM_SELECTOR_S_SHIFT ; 
 int SVM_SELECTOR_TYPE_MASK ; 
 int VCPU_SREG_SS ; 
 int /*<<< orphan*/  VMCB_SEG ; 
 int /*<<< orphan*/  mark_dirty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 struct vmcb_seg* svm_seg (struct kvm_vcpu*,int) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_set_segment(struct kvm_vcpu *vcpu,
			    struct kvm_segment *var, int seg)
{
	struct vcpu_svm *svm = to_svm(vcpu);
	struct vmcb_seg *s = svm_seg(vcpu, seg);

	s->base = var->base;
	s->limit = var->limit;
	s->selector = var->selector;
	s->attrib = (var->type & SVM_SELECTOR_TYPE_MASK);
	s->attrib |= (var->s & 1) << SVM_SELECTOR_S_SHIFT;
	s->attrib |= (var->dpl & 3) << SVM_SELECTOR_DPL_SHIFT;
	s->attrib |= ((var->present & 1) && !var->unusable) << SVM_SELECTOR_P_SHIFT;
	s->attrib |= (var->avl & 1) << SVM_SELECTOR_AVL_SHIFT;
	s->attrib |= (var->l & 1) << SVM_SELECTOR_L_SHIFT;
	s->attrib |= (var->db & 1) << SVM_SELECTOR_DB_SHIFT;
	s->attrib |= (var->g & 1) << SVM_SELECTOR_G_SHIFT;

	/*
	 * This is always accurate, except if SYSRET returned to a segment
	 * with SS.DPL != 3.  Intel does not have this quirk, and always
	 * forces SS.DPL to 3 on sysret, so we ignore that case; fixing it
	 * would entail passing the CPL to userspace and back.
	 */
	if (seg == VCPU_SREG_SS)
		/* This is symmetric with svm_get_segment() */
		svm->vmcb->save.cpl = (var->dpl & 3);

	mark_dirty(svm->vmcb, VMCB_SEG);
}