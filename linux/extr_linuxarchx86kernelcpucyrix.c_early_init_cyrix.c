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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CYRIX_ARR ; 
 int /*<<< orphan*/  __do_cyrix_devid (unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void early_init_cyrix(struct cpuinfo_x86 *c)
{
	unsigned char dir0, dir0_msn, dir1 = 0;

	__do_cyrix_devid(&dir0, &dir1);
	dir0_msn = dir0 >> 4; /* identifies CPU "family"   */

	switch (dir0_msn) {
	case 3: /* 6x86/6x86L */
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		break;
	case 5: /* 6x86MX/M II */
		/* Emulate MTRRs using Cyrix's ARRs. */
		set_cpu_cap(c, X86_FEATURE_CYRIX_ARR);
		break;
	}
}