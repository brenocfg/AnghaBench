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
 int /*<<< orphan*/  PAGE_SIZE ; 
 long __flush_cache_user_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 unsigned long min (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long
__do_compat_cache_op(unsigned long start, unsigned long end)
{
	long ret;

	do {
		unsigned long chunk = min(PAGE_SIZE, end - start);

		if (fatal_signal_pending(current))
			return 0;

		ret = __flush_cache_user_range(start, start + chunk);
		if (ret)
			return ret;

		cond_resched();
		start += chunk;
	} while (start < end);

	return 0;
}