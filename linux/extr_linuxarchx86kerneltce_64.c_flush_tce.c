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
 int /*<<< orphan*/  X86_FEATURE_CLFLUSH ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clflush (void*) ; 
 int /*<<< orphan*/  wbinvd () ; 

__attribute__((used)) static inline void flush_tce(void* tceaddr)
{
	/* a single tce can't cross a cache line */
	if (boot_cpu_has(X86_FEATURE_CLFLUSH))
		clflush(tceaddr);
	else
		wbinvd();
}