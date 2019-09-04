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
typedef  unsigned long u64 ;
typedef  enum page_cache_mode { ____Placeholder_page_cache_mode } page_cache_mode ;
struct TYPE_2__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long __pa (scalar_t__) ; 
 scalar_t__ __va (unsigned long) ; 
 int /*<<< orphan*/  cattr_name (int) ; 
 TYPE_1__* current ; 
 scalar_t__ high_memory ; 
 scalar_t__ ioremap_change_attr (unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  page_is_ram (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 

int kernel_map_sync_memtype(u64 base, unsigned long size,
			    enum page_cache_mode pcm)
{
	unsigned long id_sz;

	if (base > __pa(high_memory-1))
		return 0;

	/*
	 * some areas in the middle of the kernel identity range
	 * are not mapped, like the PCI space.
	 */
	if (!page_is_ram(base >> PAGE_SHIFT))
		return 0;

	id_sz = (__pa(high_memory-1) <= base + size) ?
				__pa(high_memory) - base :
				size;

	if (ioremap_change_attr((unsigned long)__va(base), id_sz, pcm) < 0) {
		pr_info("x86/PAT: %s:%d ioremap_change_attr failed %s for [mem %#010Lx-%#010Lx]\n",
			current->comm, current->pid,
			cattr_name(pcm),
			base, (unsigned long long)(base + size-1));
		return -EINVAL;
	}
	return 0;
}