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
struct sgp_data {scalar_t__ iaq_init_start_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (long const,long const) ; 

__attribute__((used)) static void sgp_iaq_thread_sleep_until(const struct sgp_data *data,
				       unsigned long sleep_jiffies)
{
	const long IAQ_POLL = 50000;

	while (!time_after(jiffies, sleep_jiffies)) {
		usleep_range(IAQ_POLL, IAQ_POLL + 10000);
		if (kthread_should_stop() || data->iaq_init_start_jiffies == 0)
			return;
	}
}