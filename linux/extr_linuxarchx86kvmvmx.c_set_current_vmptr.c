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
struct TYPE_4__ {int sync_shadow_vmcs; int dirty_vmcs12; int /*<<< orphan*/  current_vmptr; } ;
struct TYPE_3__ {int /*<<< orphan*/  shadow_vmcs; } ;
struct vcpu_vmx {TYPE_2__ nested; TYPE_1__ vmcs01; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  SECONDARY_EXEC_SHADOW_VMCS ; 
 int /*<<< orphan*/  SECONDARY_VM_EXEC_CONTROL ; 
 int /*<<< orphan*/  VMCS_LINK_POINTER ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 scalar_t__ enable_shadow_vmcs ; 
 int /*<<< orphan*/  vmcs_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_current_vmptr(struct vcpu_vmx *vmx, gpa_t vmptr)
{
	vmx->nested.current_vmptr = vmptr;
	if (enable_shadow_vmcs) {
		vmcs_set_bits(SECONDARY_VM_EXEC_CONTROL,
			      SECONDARY_EXEC_SHADOW_VMCS);
		vmcs_write64(VMCS_LINK_POINTER,
			     __pa(vmx->vmcs01.shadow_vmcs));
		vmx->nested.sync_shadow_vmcs = true;
	}
	vmx->nested.dirty_vmcs12 = true;
}