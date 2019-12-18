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
struct io_tracker {scalar_t__ idle_time; scalar_t__ in_flight; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool __iot_idle_for(struct io_tracker *iot, unsigned long jifs)
{
	if (iot->in_flight)
		return false;

	return time_after(jiffies, iot->idle_time + jifs);
}