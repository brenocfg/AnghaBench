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
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {scalar_t__ nested_run_pending; } ;
struct TYPE_4__ {TYPE_1__ nested; } ;

/* Variables and functions */
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int vmx_smi_allowed(struct kvm_vcpu *vcpu)
{
	/* we need a nested vmexit to enter SMM, postpone if run is pending */
	if (to_vmx(vcpu)->nested.nested_run_pending)
		return 0;
	return 1;
}