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
struct input_polled_dev {int /*<<< orphan*/  work; int /*<<< orphan*/  poll_interval; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long round_jiffies_relative (unsigned long) ; 
 int /*<<< orphan*/  system_freezable_wq ; 

__attribute__((used)) static void input_polldev_queue_work(struct input_polled_dev *dev)
{
	unsigned long delay;

	delay = msecs_to_jiffies(dev->poll_interval);
	if (delay >= HZ)
		delay = round_jiffies_relative(delay);

	queue_delayed_work(system_freezable_wq, &dev->work, delay);
}