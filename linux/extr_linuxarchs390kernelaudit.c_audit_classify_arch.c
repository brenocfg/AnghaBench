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

int audit_classify_arch(int arch)
{
#ifdef CONFIG_COMPAT
	if (arch == AUDIT_ARCH_S390)
		return 1;
#endif
	return 0;
}