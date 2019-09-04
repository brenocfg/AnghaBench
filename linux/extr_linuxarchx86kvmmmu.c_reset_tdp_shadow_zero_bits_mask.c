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
struct rsvd_bits_validate {int /*<<< orphan*/ ** rsvd_bits_mask; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int shadow_root_level; struct rsvd_bits_validate shadow_zero_check; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_phys_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_GBPAGES ; 
 int /*<<< orphan*/  __reset_rsvds_bits_mask (struct kvm_vcpu*,struct rsvd_bits_validate*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  __reset_rsvds_bits_mask_ept (struct rsvd_bits_validate*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_is_amd () ; 
 int /*<<< orphan*/  shadow_me_mask ; 

__attribute__((used)) static void
reset_tdp_shadow_zero_bits_mask(struct kvm_vcpu *vcpu,
				struct kvm_mmu *context)
{
	struct rsvd_bits_validate *shadow_zero_check;
	int i;

	shadow_zero_check = &context->shadow_zero_check;

	if (boot_cpu_is_amd())
		__reset_rsvds_bits_mask(vcpu, shadow_zero_check,
					boot_cpu_data.x86_phys_bits,
					context->shadow_root_level, false,
					boot_cpu_has(X86_FEATURE_GBPAGES),
					true, true);
	else
		__reset_rsvds_bits_mask_ept(shadow_zero_check,
					    boot_cpu_data.x86_phys_bits,
					    false);

	if (!shadow_me_mask)
		return;

	for (i = context->shadow_root_level; --i >= 0;) {
		shadow_zero_check->rsvd_bits_mask[0][i] &= ~shadow_me_mask;
		shadow_zero_check->rsvd_bits_mask[1][i] &= ~shadow_me_mask;
	}
}