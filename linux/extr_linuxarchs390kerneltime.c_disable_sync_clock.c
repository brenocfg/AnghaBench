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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_andnot (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clock_sync_word ; 
 int /*<<< orphan*/ * this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_sync_clock(void *dummy)
{
	atomic_t *sw_ptr = this_cpu_ptr(&clock_sync_word);
	/*
	 * Clear the in-sync bit 2^31. All get_phys_clock calls will
	 * fail until the sync bit is turned back on. In addition
	 * increase the "sequence" counter to avoid the race of an
	 * stp event and the complete recovery against get_phys_clock.
	 */
	atomic_andnot(0x80000000, sw_ptr);
	atomic_inc(sw_ptr);
}