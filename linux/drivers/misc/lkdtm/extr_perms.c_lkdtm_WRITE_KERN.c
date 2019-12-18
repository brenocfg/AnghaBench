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
 scalar_t__ do_nothing ; 
 int /*<<< orphan*/  do_overwritten () ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  pr_info (char*,size_t,unsigned char*) ; 

void lkdtm_WRITE_KERN(void)
{
	size_t size;
	unsigned char *ptr;

	size = (unsigned long)do_overwritten - (unsigned long)do_nothing;
	ptr = (unsigned char *)do_overwritten;

	pr_info("attempting bad %zu byte write at %px\n", size, ptr);
	memcpy(ptr, (unsigned char *)do_nothing, size);
	flush_icache_range((unsigned long)ptr, (unsigned long)(ptr + size));

	do_overwritten();
}