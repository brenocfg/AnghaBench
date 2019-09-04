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
struct list_head {int dummy; } ;
struct TYPE_5__ {scalar_t__ (* sync_page ) (struct kvm_vcpu*,struct kvm_mmu_page*) ;} ;
struct TYPE_6__ {TYPE_2__ mmu; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_3__ arch; } ;
struct TYPE_4__ {int cr4_pae; } ;
struct kvm_mmu_page {TYPE_1__ role; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_prepare_zap_page (int /*<<< orphan*/ ,struct kvm_mmu_page*,struct list_head*) ; 
 scalar_t__ stub1 (struct kvm_vcpu*,struct kvm_mmu_page*) ; 

__attribute__((used)) static bool __kvm_sync_page(struct kvm_vcpu *vcpu, struct kvm_mmu_page *sp,
			    struct list_head *invalid_list)
{
	if (sp->role.cr4_pae != !!is_pae(vcpu)
	    || vcpu->arch.mmu.sync_page(vcpu, sp) == 0) {
		kvm_mmu_prepare_zap_page(vcpu->kvm, sp, invalid_list);
		return false;
	}

	return true;
}