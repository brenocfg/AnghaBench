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
struct TYPE_5__ {int /*<<< orphan*/  maar; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  kscratch_mask; } ;
struct TYPE_6__ {TYPE_1__ guest; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ __arch_hweight8 (int /*<<< orphan*/ ) ; 
 TYPE_3__* cpu_data ; 
 scalar_t__ cpu_guest_has_badinstr ; 
 scalar_t__ cpu_guest_has_badinstrp ; 
 scalar_t__ cpu_guest_has_contextconfig ; 
 int /*<<< orphan*/  cpu_guest_has_dyn_maar ; 
 scalar_t__ cpu_guest_has_htw ; 
 scalar_t__ cpu_guest_has_maar ; 
 scalar_t__ cpu_guest_has_segments ; 
 scalar_t__ cpu_guest_has_userlocal ; 
 int /*<<< orphan*/  kvm_vz_get_one_regs ; 
 int /*<<< orphan*/  kvm_vz_get_one_regs_contextconfig ; 
 int /*<<< orphan*/  kvm_vz_get_one_regs_htw ; 
 int /*<<< orphan*/  kvm_vz_get_one_regs_segments ; 

__attribute__((used)) static unsigned long kvm_vz_num_regs(struct kvm_vcpu *vcpu)
{
	unsigned long ret;

	ret = ARRAY_SIZE(kvm_vz_get_one_regs);
	if (cpu_guest_has_userlocal)
		++ret;
	if (cpu_guest_has_badinstr)
		++ret;
	if (cpu_guest_has_badinstrp)
		++ret;
	if (cpu_guest_has_contextconfig)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_contextconfig);
	if (cpu_guest_has_segments)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_segments);
	if (cpu_guest_has_htw)
		ret += ARRAY_SIZE(kvm_vz_get_one_regs_htw);
	if (cpu_guest_has_maar && !cpu_guest_has_dyn_maar)
		ret += 1 + ARRAY_SIZE(vcpu->arch.maar);
	ret += __arch_hweight8(cpu_data[0].guest.kscratch_mask);

	return ret;
}