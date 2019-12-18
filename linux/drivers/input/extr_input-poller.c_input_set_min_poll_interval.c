#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct input_dev {TYPE_1__* poller; } ;
struct TYPE_2__ {unsigned int poll_interval_min; } ;

/* Variables and functions */
 scalar_t__ input_dev_ensure_poller (struct input_dev*) ; 

void input_set_min_poll_interval(struct input_dev *dev, unsigned int interval)
{
	if (input_dev_ensure_poller(dev))
		dev->poller->poll_interval_min = interval;
}