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
struct link {scalar_t__ watchdog_interval; int /*<<< orphan*/  watchdog_work; int /*<<< orphan*/  work; } ;
struct rt2x00_dev {struct link link; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ WATCHDOG_INTERVAL ; 
 int /*<<< orphan*/  rt2x00link_tuner ; 
 int /*<<< orphan*/  rt2x00link_watchdog ; 

void rt2x00link_register(struct rt2x00_dev *rt2x00dev)
{
	struct link *link = &rt2x00dev->link;

	INIT_DELAYED_WORK(&link->work, rt2x00link_tuner);
	INIT_DELAYED_WORK(&link->watchdog_work, rt2x00link_watchdog);

	if (link->watchdog_interval == 0)
		link->watchdog_interval = WATCHDOG_INTERVAL;
}