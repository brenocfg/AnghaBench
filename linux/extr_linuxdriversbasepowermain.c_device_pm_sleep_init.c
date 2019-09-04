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
struct TYPE_2__ {int is_prepared; int is_suspended; int is_noirq_suspended; int is_late_suspended; int /*<<< orphan*/  entry; int /*<<< orphan*/ * wakeup; int /*<<< orphan*/  completion; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

void device_pm_sleep_init(struct device *dev)
{
	dev->power.is_prepared = false;
	dev->power.is_suspended = false;
	dev->power.is_noirq_suspended = false;
	dev->power.is_late_suspended = false;
	init_completion(&dev->power.completion);
	complete_all(&dev->power.completion);
	dev->power.wakeup = NULL;
	INIT_LIST_HEAD(&dev->power.entry);
}