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

/* Variables and functions */
 int KVM_CPUID_FEATURES ; 
 unsigned int cpuid_eax (int) ; 
 int kvm_cpuid_base () ; 

unsigned int kvm_arch_para_features(void)
{
	return cpuid_eax(kvm_cpuid_base() | KVM_CPUID_FEATURES);
}