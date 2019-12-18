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
struct input_dev_poller {int poll_interval; int poll_interval_max; } ;

/* Variables and functions */

void input_dev_poller_finalize(struct input_dev_poller *poller)
{
	if (!poller->poll_interval)
		poller->poll_interval = 500;
	if (!poller->poll_interval_max)
		poller->poll_interval_max = poller->poll_interval;
}