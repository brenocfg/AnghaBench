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
struct TYPE_4__ {int misc_low; } ;
struct TYPE_5__ {TYPE_1__ msrs; } ;
struct TYPE_6__ {TYPE_2__ nested; } ;

/* Variables and functions */
 int VMX_MISC_ZERO_LEN_INS ; 
 TYPE_3__* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool nested_cpu_has_zero_length_injection(struct kvm_vcpu *vcpu)
{
	return to_vmx(vcpu)->nested.msrs.misc_low & VMX_MISC_ZERO_LEN_INS;
}