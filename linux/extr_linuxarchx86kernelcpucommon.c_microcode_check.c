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
struct cpuinfo_x86 {int /*<<< orphan*/  x86_capability; int /*<<< orphan*/  cpuid_level; } ;
struct TYPE_2__ {int /*<<< orphan*/  x86_capability; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  cpuid_eax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cpu_cap (struct cpuinfo_x86*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  perf_check_microcode () ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void microcode_check(void)
{
	struct cpuinfo_x86 info;

	perf_check_microcode();

	/* Reload CPUID max function as it might've changed. */
	info.cpuid_level = cpuid_eax(0);

	/*
	 * Copy all capability leafs to pick up the synthetic ones so that
	 * memcmp() below doesn't fail on that. The ones coming from CPUID will
	 * get overwritten in get_cpu_cap().
	 */
	memcpy(&info.x86_capability, &boot_cpu_data.x86_capability, sizeof(info.x86_capability));

	get_cpu_cap(&info);

	if (!memcmp(&info.x86_capability, &boot_cpu_data.x86_capability, sizeof(info.x86_capability)))
		return;

	pr_warn("x86/CPU: CPU features have changed after loading microcode, but might not take effect.\n");
	pr_warn("x86/CPU: Please consider either early loading through initrd/built-in or a potential BIOS update.\n");
}