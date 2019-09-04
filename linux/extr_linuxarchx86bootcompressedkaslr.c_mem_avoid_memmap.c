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
struct TYPE_2__ {unsigned long long start; unsigned long long size; } ;

/* Variables and functions */
 int MAX_MEMMAP_REGIONS ; 
 int MEM_AVOID_MEMMAP_BEGIN ; 
 TYPE_1__* mem_avoid ; 
 unsigned long long mem_limit ; 
 int memmap_too_large ; 
 int parse_memmap (char*,unsigned long long*,unsigned long long*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static void mem_avoid_memmap(char *str)
{
	static int i;

	if (i >= MAX_MEMMAP_REGIONS)
		return;

	while (str && (i < MAX_MEMMAP_REGIONS)) {
		int rc;
		unsigned long long start, size;
		char *k = strchr(str, ',');

		if (k)
			*k++ = 0;

		rc = parse_memmap(str, &start, &size);
		if (rc < 0)
			break;
		str = k;

		if (start == 0) {
			/* Store the specified memory limit if size > 0 */
			if (size > 0)
				mem_limit = size;

			continue;
		}

		mem_avoid[MEM_AVOID_MEMMAP_BEGIN + i].start = start;
		mem_avoid[MEM_AVOID_MEMMAP_BEGIN + i].size = size;
		i++;
	}

	/* More than 4 memmaps, fail kaslr */
	if ((i >= MAX_MEMMAP_REGIONS) && str)
		memmap_too_large = true;
}