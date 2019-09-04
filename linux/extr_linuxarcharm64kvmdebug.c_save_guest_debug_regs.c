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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  mdscr_el1; } ;
struct TYPE_4__ {TYPE_1__ guest_debug_preserved; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDSCR_EL1 ; 
 int /*<<< orphan*/  trace_kvm_arm_set_dreg32 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_read_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void save_guest_debug_regs(struct kvm_vcpu *vcpu)
{
	u64 val = vcpu_read_sys_reg(vcpu, MDSCR_EL1);

	vcpu->arch.guest_debug_preserved.mdscr_el1 = val;

	trace_kvm_arm_set_dreg32("Saved MDSCR_EL1",
				vcpu->arch.guest_debug_preserved.mdscr_el1);
}