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
struct TYPE_2__ {unsigned long x86_clflush_size; } ;

/* Variables and functions */
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  clflushopt (void*) ; 
 int /*<<< orphan*/  mb () ; 

void clflush_cache_range(void *vaddr, unsigned int size)
{
	const unsigned long clflush_size = boot_cpu_data.x86_clflush_size;
	void *p = (void *)((unsigned long)vaddr & ~(clflush_size - 1));
	void *vend = vaddr + size;

	if (p >= vend)
		return;

	mb();

	for (; p < vend; p += clflush_size)
		clflushopt(p);

	mb();
}