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
struct TYPE_2__ {int is_late_suspended; int is_suspended; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */

void dev_pm_skip_next_resume_phases(struct device *dev)
{
	dev->power.is_late_suspended = false;
	dev->power.is_suspended = false;
}