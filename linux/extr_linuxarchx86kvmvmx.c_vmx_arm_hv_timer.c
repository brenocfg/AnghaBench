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
typedef  int /*<<< orphan*/  u32 ;
struct vcpu_vmx {TYPE_1__* loaded_vmcs; } ;
struct TYPE_2__ {int hv_timer_armed; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIN_BASED_VMX_PREEMPTION_TIMER ; 
 int /*<<< orphan*/  PIN_BASED_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  VMX_PREEMPTION_TIMER_VALUE ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_arm_hv_timer(struct vcpu_vmx *vmx, u32 val)
{
	vmcs_write32(VMX_PREEMPTION_TIMER_VALUE, val);
	if (!vmx->loaded_vmcs->hv_timer_armed)
		vmcs_set_bits(PIN_BASED_VM_EXEC_CONTROL,
			      PIN_BASED_VMX_PREEMPTION_TIMER);
	vmx->loaded_vmcs->hv_timer_armed = true;
}