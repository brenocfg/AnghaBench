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
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {scalar_t__ nested_run_pending; } ;
struct TYPE_6__ {TYPE_2__* loaded_vmcs; TYPE_1__ nested; } ;
struct TYPE_5__ {scalar_t__ soft_vnmi_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_INTERRUPTIBILITY_INFO ; 
 int GUEST_INTR_STATE_MOV_SS ; 
 int GUEST_INTR_STATE_NMI ; 
 int GUEST_INTR_STATE_STI ; 
 int /*<<< orphan*/  enable_vnmi ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 
 int vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmx_nmi_allowed(struct kvm_vcpu *vcpu)
{
	if (to_vmx(vcpu)->nested.nested_run_pending)
		return 0;

	if (!enable_vnmi &&
	    to_vmx(vcpu)->loaded_vmcs->soft_vnmi_blocked)
		return 0;

	return	!(vmcs_read32(GUEST_INTERRUPTIBILITY_INFO) &
		  (GUEST_INTR_STATE_MOV_SS | GUEST_INTR_STATE_STI
		   | GUEST_INTR_STATE_NMI));
}