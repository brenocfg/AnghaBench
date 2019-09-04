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
struct x86_exception {int dummy; } ;
struct TYPE_4__ {TYPE_1__* walk_mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* gva_to_gpa ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct x86_exception*) ; 

gpa_t kvm_mmu_gva_to_gpa_system(struct kvm_vcpu *vcpu, gva_t gva,
				struct x86_exception *exception)
{
	return vcpu->arch.walk_mmu->gva_to_gpa(vcpu, gva, 0, exception);
}