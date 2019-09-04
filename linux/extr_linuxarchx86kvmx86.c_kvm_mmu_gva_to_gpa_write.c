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
typedef  int /*<<< orphan*/  u32 ;
struct x86_exception {int dummy; } ;
struct TYPE_5__ {TYPE_1__* walk_mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_6__ {int (* get_cpl ) (struct kvm_vcpu*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* gva_to_gpa ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PFERR_USER_MASK ; 
 int /*<<< orphan*/  PFERR_WRITE_MASK ; 
 TYPE_3__* kvm_x86_ops ; 
 int stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ; 

gpa_t kvm_mmu_gva_to_gpa_write(struct kvm_vcpu *vcpu, gva_t gva,
			       struct x86_exception *exception)
{
	u32 access = (kvm_x86_ops->get_cpl(vcpu) == 3) ? PFERR_USER_MASK : 0;
	access |= PFERR_WRITE_MASK;
	return vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, access, exception);
}