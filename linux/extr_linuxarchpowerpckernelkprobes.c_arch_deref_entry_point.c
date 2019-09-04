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

unsigned long arch_deref_entry_point(void *entry)
{
#ifdef PPC64_ELF_ABI_v1
	if (!kernel_text_address((unsigned long)entry))
		return ppc_global_function_entry(entry);
	else
#endif
		return (unsigned long)entry;
}