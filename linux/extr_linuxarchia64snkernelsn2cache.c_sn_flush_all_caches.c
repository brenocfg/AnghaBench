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
 unsigned long RGN_BASE (int /*<<< orphan*/ ) ; 
 unsigned long RGN_BITS ; 
 int /*<<< orphan*/  RGN_KERNEL ; 
 int /*<<< orphan*/  RGN_UNCACHED ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 scalar_t__ is_shub1 () ; 
 int /*<<< orphan*/  mb () ; 

void
sn_flush_all_caches(long flush_addr, long bytes)
{
	unsigned long addr = flush_addr;

	/* SHub1 requires a cached address */
	if (is_shub1() && (addr & RGN_BITS) == RGN_BASE(RGN_UNCACHED))
		addr = (addr - RGN_BASE(RGN_UNCACHED)) + RGN_BASE(RGN_KERNEL);

	flush_icache_range(addr, addr + bytes);
	/*
	 * The last call may have returned before the caches
	 * were actually flushed, so we call it again to make
	 * sure.
	 */
	flush_icache_range(addr, addr + bytes);
	mb();
}