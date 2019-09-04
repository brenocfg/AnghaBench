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
typedef  int uint64_t ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int msr_ia32_feature_control_valid_bits; } ;

/* Variables and functions */
 TYPE_1__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool vmx_feature_control_msr_valid(struct kvm_vcpu *vcpu,
						 uint64_t val)
{
	uint64_t valid_bits = to_vmx(vcpu)->msr_ia32_feature_control_valid_bits;

	return !(val & ~valid_bits);
}