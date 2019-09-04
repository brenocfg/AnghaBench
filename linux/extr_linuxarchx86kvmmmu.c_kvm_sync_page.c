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
struct kvm_mmu_page {int dummy; } ;

/* Variables and functions */
 int __kvm_sync_page (struct kvm_vcpu*,struct kvm_mmu_page*,struct list_head*) ; 
 int /*<<< orphan*/  kvm_unlink_unsync_page (int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 

__attribute__((used)) static bool kvm_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp,
			 struct list_head *invalid_list)
{
	kvm_unlink_unsync_page(vcpu->kvm, sp);
	return __kvm_sync_page(vcpu, sp, invalid_list);
}