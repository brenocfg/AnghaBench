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

__attribute__((used)) static inline int overlaps_initrd(unsigned long start, unsigned long size)
{
#ifdef CONFIG_BLK_DEV_INITRD
	if (!initrd_start)
		return 0;

	return	(start + size) > _ALIGN_DOWN(initrd_start, PAGE_SIZE) &&
			start <= _ALIGN_UP(initrd_end, PAGE_SIZE);
#else
	return 0;
#endif
}