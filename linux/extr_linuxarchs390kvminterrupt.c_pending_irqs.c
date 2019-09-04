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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct TYPE_3__ {int /*<<< orphan*/  gisa; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long IRQ_PEND_IO_ISC_7 ; 
 unsigned long kvm_s390_gisa_get_ipm (int /*<<< orphan*/ ) ; 
 unsigned long pending_irqs_no_gisa (struct kvm_vcpu*) ; 

__attribute__((used)) static inline unsigned long pending_irqs(struct kvm_vcpu *vcpu)
{
	return pending_irqs_no_gisa(vcpu) |
		kvm_s390_gisa_get_ipm(vcpu->kvm->arch.gisa) << IRQ_PEND_IO_ISC_7;
}