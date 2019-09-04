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
struct kvm_vcpu {struct kvm* kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  kvmclock_update_work; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVMCLOCK_UPDATE_DELAY ; 
 int /*<<< orphan*/  KVM_REQ_CLOCK_UPDATE ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_gen_kvmclock_update(struct kvm_vcpu *v)
{
	struct kvm *kvm = v->kvm;

	kvm_make_request(KVM_REQ_CLOCK_UPDATE, v);
	schedule_delayed_work(&kvm->arch.kvmclock_update_work,
					KVMCLOCK_UPDATE_DELAY);
}