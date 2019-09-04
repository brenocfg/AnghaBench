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
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_3__ {int /*<<< orphan*/  cr3; int /*<<< orphan*/  regs_avail; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* decache_cr3 ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_EXREG_CR3 ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ulong kvm_read_cr3(struct kvm_vcpu *vcpu)
{
	if (!test_bit(VCPU_EXREG_CR3, (ulong *)&vcpu->arch.regs_avail))
		kvm_x86_ops->decache_cr3(vcpu);
	return vcpu->arch.cr3;
}