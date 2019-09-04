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
struct TYPE_3__ {scalar_t__ count_hz; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int gtoffset_mask; } ;

/* Variables and functions */
 TYPE_2__ current_cpu_data ; 
 scalar_t__ kvm_mips_count_disabled (struct kvm_vcpu*) ; 
 scalar_t__ mips_hpt_frequency ; 

__attribute__((used)) static bool kvm_vz_should_use_htimer(struct kvm_vcpu *vcpu)
{
	if (kvm_mips_count_disabled(vcpu))
		return false;

	/* Chosen frequency must match real frequency */
	if (mips_hpt_frequency != vcpu->arch.count_hz)
		return false;

	/* We don't support a CP0_GTOffset with fewer bits than CP0_Count */
	if (current_cpu_data.gtoffset_mask != 0xffffffff)
		return false;

	return true;
}