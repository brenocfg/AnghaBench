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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ MEM_GOING_OFFLINE ; 
 scalar_t__ MEM_OFFLINE ; 
 scalar_t__ MEM_ONLINE ; 
 int /*<<< orphan*/  change_memblock_state ; 
 int /*<<< orphan*/  check_memblock_online ; 
 scalar_t__ offline_pages (scalar_t__,scalar_t__) ; 
 scalar_t__ walk_memory_range (scalar_t__,scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool memtrace_offline_pages(u32 nid, u64 start_pfn, u64 nr_pages)
{
	u64 end_pfn = start_pfn + nr_pages - 1;

	if (walk_memory_range(start_pfn, end_pfn, NULL,
	    check_memblock_online))
		return false;

	walk_memory_range(start_pfn, end_pfn, (void *)MEM_GOING_OFFLINE,
			  change_memblock_state);

	if (offline_pages(start_pfn, nr_pages)) {
		walk_memory_range(start_pfn, end_pfn, (void *)MEM_ONLINE,
				  change_memblock_state);
		return false;
	}

	walk_memory_range(start_pfn, end_pfn, (void *)MEM_OFFLINE,
			  change_memblock_state);


	return true;
}