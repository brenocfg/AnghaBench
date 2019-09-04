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
struct vcpu_svm {TYPE_2__* vmcb; } ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_3__ {int /*<<< orphan*/  asid; } ;
struct TYPE_4__ {TYPE_1__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  invlpga (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_flush_tlb_gva(struct kvm_vcpu *vcpu, gva_t gva)
{
	struct vcpu_svm *svm = to_svm(vcpu);

	invlpga(gva, svm->vmcb->control.asid);
}