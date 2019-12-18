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
struct timespec64 {int dummy; } ;
struct timespec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 
 struct timespec64 timespec64_sub (struct timespec64,struct timespec64) ; 
 unsigned long timespec64_to_jiffies (struct timespec64*) ; 
 struct timespec64 timespec_to_timespec64 (struct timespec const) ; 

__attribute__((used)) static inline unsigned long etnaviv_timeout_to_jiffies(
	const struct timespec *timeout)
{
	struct timespec64 ts, to;

	to = timespec_to_timespec64(*timeout);

	ktime_get_ts64(&ts);

	/* timeouts before "now" have already expired */
	if (timespec64_compare(&to, &ts) <= 0)
		return 0;

	ts = timespec64_sub(to, ts);

	return timespec64_to_jiffies(&ts);
}