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
struct ltc2497_st {int /*<<< orphan*/  time_prev; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int ERESTARTSYS ; 
 scalar_t__ LTC2497_CONVERSION_TIME_MS ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ msleep_interruptible (scalar_t__) ; 

__attribute__((used)) static int ltc2497_wait_conv(struct ltc2497_st *st)
{
	s64 time_elapsed;

	time_elapsed = ktime_ms_delta(ktime_get(), st->time_prev);

	if (time_elapsed < LTC2497_CONVERSION_TIME_MS) {
		/* delay if conversion time not passed
		 * since last read or write
		 */
		if (msleep_interruptible(
		    LTC2497_CONVERSION_TIME_MS - time_elapsed))
			return -ERESTARTSYS;

		return 0;
	}

	if (time_elapsed - LTC2497_CONVERSION_TIME_MS <= 0) {
		/* We're in automatic mode -
		 * so the last reading is stil not outdated
		 */
		return 0;
	}

	return 1;
}