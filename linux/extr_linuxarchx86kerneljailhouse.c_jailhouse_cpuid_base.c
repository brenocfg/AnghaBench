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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ cpuid_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_HYPERVISOR ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hypervisor_cpuid_base (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t jailhouse_cpuid_base(void)
{
	if (boot_cpu_data.cpuid_level < 0 ||
	    !boot_cpu_has(X86_FEATURE_HYPERVISOR))
		return 0;

	return hypervisor_cpuid_base("Jailhouse\0\0\0", 0);
}