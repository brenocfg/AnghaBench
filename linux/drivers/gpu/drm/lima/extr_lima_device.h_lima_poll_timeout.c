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
struct lima_ip {int dummy; } ;
typedef  scalar_t__ (* lima_poll_func_t ) (struct lima_ip*) ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static inline int lima_poll_timeout(struct lima_ip *ip, lima_poll_func_t func,
				    int sleep_us, int timeout_us)
{
	ktime_t timeout = ktime_add_us(ktime_get(), timeout_us);

	might_sleep_if(sleep_us);
	while (1) {
		if (func(ip))
			return 0;

		if (timeout_us && ktime_compare(ktime_get(), timeout) > 0)
			return -ETIMEDOUT;

		if (sleep_us)
			usleep_range((sleep_us >> 2) + 1, sleep_us);
	}
	return 0;
}