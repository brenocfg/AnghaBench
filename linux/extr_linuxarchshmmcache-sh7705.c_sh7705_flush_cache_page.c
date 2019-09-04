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
struct flusher_data {unsigned long addr2; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __flush_dcache_page (unsigned long) ; 

__attribute__((used)) static void sh7705_flush_cache_page(void *args)
{
	struct flusher_data *data = args;
	unsigned long pfn = data->addr2;

	__flush_dcache_page(pfn << PAGE_SHIFT);
}