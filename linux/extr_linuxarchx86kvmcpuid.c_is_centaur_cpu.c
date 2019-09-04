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
struct kvm_cpuid_param {int dummy; } ;
struct TYPE_2__ {scalar_t__ x86_vendor; } ;

/* Variables and functions */
 scalar_t__ X86_VENDOR_CENTAUR ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool is_centaur_cpu(const struct kvm_cpuid_param *param)
{
	return boot_cpu_data.x86_vendor == X86_VENDOR_CENTAUR;
}