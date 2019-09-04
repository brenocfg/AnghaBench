#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  gmap; int /*<<< orphan*/  enabled_gmap; TYPE_2__* sie_block; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_4__* kvm; } ;
struct TYPE_6__ {scalar_t__ user_instr0; int /*<<< orphan*/  gmap; int /*<<< orphan*/  epdx; int /*<<< orphan*/  epoch; } ;
struct TYPE_9__ {TYPE_1__ arch; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  ictl; int /*<<< orphan*/  epdx; int /*<<< orphan*/  epoch; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICTL_OPEREXC ; 
 int /*<<< orphan*/  kvm_is_ucontrol (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  sca_add_vcpu (struct kvm_vcpu*) ; 
 scalar_t__ test_kvm_facility (TYPE_4__*,int) ; 

void kvm_arch_vcpu_postcreate(struct kvm_vcpu *vcpu)
{
	mutex_lock(&vcpu->kvm->lock);
	preempt_disable();
	vcpu->arch.sie_block->epoch = vcpu->kvm->arch.epoch;
	vcpu->arch.sie_block->epdx = vcpu->kvm->arch.epdx;
	preempt_enable();
	mutex_unlock(&vcpu->kvm->lock);
	if (!kvm_is_ucontrol(vcpu->kvm)) {
		vcpu->arch.gmap = vcpu->kvm->arch.gmap;
		sca_add_vcpu(vcpu);
	}
	if (test_kvm_facility(vcpu->kvm, 74) || vcpu->kvm->arch.user_instr0)
		vcpu->arch.sie_block->ictl |= ICTL_OPEREXC;
	/* make vcpu_load load the right gmap on the first trigger */
	vcpu->arch.enabled_gmap = vcpu->arch.gmap;
}