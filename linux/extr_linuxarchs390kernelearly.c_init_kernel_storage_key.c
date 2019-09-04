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

void init_kernel_storage_key(void)
{
#if PAGE_DEFAULT_KEY
	unsigned long end_pfn, init_pfn;

	end_pfn = PFN_UP(__pa(_end));

	for (init_pfn = 0 ; init_pfn < end_pfn; init_pfn++)
		page_set_storage_key(init_pfn << PAGE_SHIFT,
				     PAGE_DEFAULT_KEY, 0);
#endif
}