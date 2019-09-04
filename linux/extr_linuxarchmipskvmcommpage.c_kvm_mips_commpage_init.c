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
struct TYPE_2__ {int /*<<< orphan*/ * cop0; struct kvm_mips_commpage* kseg0_commpage; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mips_commpage {int /*<<< orphan*/  cop0; } ;

/* Variables and functions */

void kvm_mips_commpage_init(struct kvm_vcpu *vcpu)
{
	struct kvm_mips_commpage *page = vcpu->arch.kseg0_commpage;

	/* Specific init values for fields */
	vcpu->arch.cop0 = &page->cop0;
}