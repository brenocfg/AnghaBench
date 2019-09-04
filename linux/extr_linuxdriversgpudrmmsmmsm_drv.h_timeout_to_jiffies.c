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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 scalar_t__ ktime_compare (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 struct timespec ktime_to_timespec (int /*<<< orphan*/ ) ; 
 unsigned long timespec_to_jiffies (struct timespec*) ; 

__attribute__((used)) static inline unsigned long timeout_to_jiffies(const ktime_t *timeout)
{
	ktime_t now = ktime_get();
	unsigned long remaining_jiffies;

	if (ktime_compare(*timeout, now) < 0) {
		remaining_jiffies = 0;
	} else {
		ktime_t rem = ktime_sub(*timeout, now);
		struct timespec ts = ktime_to_timespec(rem);
		remaining_jiffies = timespec_to_jiffies(&ts);
	}

	return remaining_jiffies;
}