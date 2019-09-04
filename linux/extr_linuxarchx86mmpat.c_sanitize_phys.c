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
typedef  int u64 ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int __PHYSICAL_MASK ; 

__attribute__((used)) static u64 sanitize_phys(u64 address)
{
	/*
	 * When changing the memtype for pages containing poison allow
	 * for a "decoy" virtual address (bit 63 clear) passed to
	 * set_memory_X(). __pa() on a "decoy" address results in a
	 * physical address with bit 63 set.
	 *
	 * Decoy addresses are not present for 32-bit builds, see
	 * set_mce_nospec().
	 */
	if (IS_ENABLED(CONFIG_X86_64))
		return address & __PHYSICAL_MASK;
	return address;
}