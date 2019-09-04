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
struct TYPE_3__ {int mcg_cap; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  msr_ia32_feature_control_valid_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_CONTROL_LMCE ; 
 int MCG_LMCE_P ; 
 TYPE_2__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_setup_mce(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.mcg_cap & MCG_LMCE_P)
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits |=
			FEATURE_CONTROL_LMCE;
	else
		to_vmx(vcpu)->msr_ia32_feature_control_valid_bits &=
			~FEATURE_CONTROL_LMCE;
}