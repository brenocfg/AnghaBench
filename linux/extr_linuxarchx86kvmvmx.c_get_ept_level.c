#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ cpu_has_vmx_ept_5levels () ; 
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 

__attribute__((used)) static int get_ept_level(struct kvm_vcpu *vcpu)
{
	if (cpu_has_vmx_ept_5levels() && (cpuid_maxphyaddr(vcpu) > 48))
		return 5;
	return 4;
}