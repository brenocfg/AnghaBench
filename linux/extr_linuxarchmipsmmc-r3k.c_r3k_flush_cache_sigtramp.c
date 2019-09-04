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
 unsigned long ST0_IEC ; 
 unsigned long ST0_ISC ; 
 unsigned long ST0_SWC ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static void r3k_flush_cache_sigtramp(unsigned long addr)
{
	unsigned long flags;

	pr_debug("csigtramp[%08lx]\n", addr);

	flags = read_c0_status();

	write_c0_status(flags&~ST0_IEC);

	/* Fill the TLB to avoid an exception with caches isolated. */
	asm(	"lw\t$0, 0x000(%0)\n\t"
		"lw\t$0, 0x004(%0)\n\t"
		: : "r" (addr) );

	write_c0_status((ST0_ISC|ST0_SWC|flags)&~ST0_IEC);

	asm(	"sb\t$0, 0x000(%0)\n\t"
		"sb\t$0, 0x004(%0)\n\t"
		: : "r" (addr) );

	write_c0_status(flags);
}