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

__attribute__((used)) static void convert_to_wide(unsigned long *addr)
{
#ifdef CONFIG_64BIT
	int i;
	unsigned int *p = (unsigned int *)addr;

	if (unlikely(parisc_narrow_firmware)) {
		for (i = (NUM_PDC_RESULT-1); i >= 0; --i)
			addr[i] = p[i];
	}
#endif
}