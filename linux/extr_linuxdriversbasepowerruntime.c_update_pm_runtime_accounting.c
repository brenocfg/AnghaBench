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
struct TYPE_2__ {unsigned long accounting_timestamp; scalar_t__ disable_depth; scalar_t__ runtime_status; unsigned long suspended_jiffies; unsigned long active_jiffies; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 scalar_t__ RPM_SUSPENDED ; 
 unsigned long jiffies ; 

void update_pm_runtime_accounting(struct device *dev)
{
	unsigned long now = jiffies;
	unsigned long delta;

	delta = now - dev->power.accounting_timestamp;

	dev->power.accounting_timestamp = now;

	if (dev->power.disable_depth > 0)
		return;

	if (dev->power.runtime_status == RPM_SUSPENDED)
		dev->power.suspended_jiffies += delta;
	else
		dev->power.active_jiffies += delta;
}