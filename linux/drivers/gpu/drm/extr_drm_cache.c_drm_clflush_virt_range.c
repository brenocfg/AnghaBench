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
struct TYPE_2__ {int x86_clflush_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  X86_FEATURE_CLFLUSH ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  clflushopt (void*) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ wbinvd_on_all_cpus () ; 

void
drm_clflush_virt_range(void *addr, unsigned long length)
{
#if defined(CONFIG_X86)
	if (static_cpu_has(X86_FEATURE_CLFLUSH)) {
		const int size = boot_cpu_data.x86_clflush_size;
		void *end = addr + length;
		addr = (void *)(((unsigned long)addr) & -size);
		mb();
		for (; addr < end; addr += size)
			clflushopt(addr);
		clflushopt(end - 1); /* force serialisation */
		mb();
		return;
	}

	if (wbinvd_on_all_cpus())
		pr_err("Timed out waiting for cache flush\n");
#else
	pr_err("Architecture has no drm_cache.c support\n");
	WARN_ON_ONCE(1);
#endif
}