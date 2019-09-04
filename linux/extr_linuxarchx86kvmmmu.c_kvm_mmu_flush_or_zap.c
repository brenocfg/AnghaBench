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
struct list_head {int dummy; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  kvm_flush_remote_tlbs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_commit_zap_page (int /*<<< orphan*/ ,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

__attribute__((used)) static void kvm_mmu_flush_or_zap(struct kvm_vcpu *vcpu,
				 struct list_head *invalid_list,
				 bool remote_flush, bool local_flush)
{
	if (!list_empty(invalid_list)) {
		kvm_mmu_commit_zap_page(vcpu->kvm, invalid_list);
		return;
	}

	if (remote_flush)
		kvm_flush_remote_tlbs(vcpu->kvm);
	else if (local_flush)
		kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
}