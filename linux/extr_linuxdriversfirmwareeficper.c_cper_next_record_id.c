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
typedef  int /*<<< orphan*/  u64 ;
typedef  int time64_t ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 int ktime_get_real_seconds () ; 

u64 cper_next_record_id(void)
{
	static atomic64_t seq;

	if (!atomic64_read(&seq)) {
		time64_t time = ktime_get_real_seconds();

		/*
		 * This code is unlikely to still be needed in year 2106,
		 * but just in case, let's use a few more bits for timestamps
		 * after y2038 to be sure they keep increasing monotonically
		 * for the next few hundred years...
		 */
		if (time < 0x80000000)
			atomic64_set(&seq, (ktime_get_real_seconds()) << 32);
		else
			atomic64_set(&seq, 0x8000000000000000ull |
					   ktime_get_real_seconds() << 24);
	}

	return atomic64_inc_return(&seq);
}