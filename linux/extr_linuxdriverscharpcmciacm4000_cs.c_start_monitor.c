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
struct cm4000_dev {int monitor_running; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGP (int,struct cm4000_dev*,char*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_card ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_monitor(struct cm4000_dev *dev)
{
	DEBUGP(3, dev, "-> start_monitor\n");
	if (!dev->monitor_running) {
		DEBUGP(5, dev, "create, init and add timer\n");
		timer_setup(&dev->timer, monitor_card, 0);
		dev->monitor_running = 1;
		mod_timer(&dev->timer, jiffies);
	} else
		DEBUGP(5, dev, "monitor already running\n");
	DEBUGP(3, dev, "<- start_monitor\n");
}