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
struct TYPE_3__ {int /*<<< orphan*/  nmi_pending; int /*<<< orphan*/  nmi_queued; scalar_t__ nmi_injected; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ (* get_nmi_mask ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static void process_nmi(struct kvm_vcpu *vcpu)
{
	unsigned limit = 2;

	/*
	 * x86 is limited to one NMI running, and one NMI pending after it.
	 * If an NMI is already in progress, limit further NMIs to just one.
	 * Otherwise, allow two (and we'll inject the first one immediately).
	 */
	if (kvm_x86_ops->get_nmi_mask(vcpu) || vcpu->arch.nmi_injected)
		limit = 1;

	vcpu->arch.nmi_pending += atomic_xchg(&vcpu->arch.nmi_queued, 0);
	vcpu->arch.nmi_pending = min(vcpu->arch.nmi_pending, limit);
	kvm_make_request(KVM_REQ_EVENT, vcpu);
}