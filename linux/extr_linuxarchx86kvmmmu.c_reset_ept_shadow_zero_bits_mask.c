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
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int /*<<< orphan*/  shadow_zero_check; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_phys_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  __reset_rsvds_bits_mask_ept (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static void
reset_ept_shadow_zero_bits_mask(struct kvm_vcpu *vcpu,
				struct kvm_mmu *context, bool execonly)
{
	__reset_rsvds_bits_mask_ept(&context->shadow_zero_check,
				    boot_cpu_data.x86_phys_bits, execonly);
}