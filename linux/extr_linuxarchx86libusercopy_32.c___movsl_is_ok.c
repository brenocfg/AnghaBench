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

__attribute__((used)) static inline int __movsl_is_ok(unsigned long a1, unsigned long a2, unsigned long n)
{
#ifdef CONFIG_X86_INTEL_USERCOPY
	if (n >= 64 && ((a1 ^ a2) & movsl_mask.mask))
		return 0;
#endif
	return 1;
}