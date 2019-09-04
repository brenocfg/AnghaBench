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
struct TYPE_2__ {int /*<<< orphan*/  request; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPM_REQ_NONE ; 
 int /*<<< orphan*/  pm_runtime_deactivate_timer (struct device*) ; 

__attribute__((used)) static void pm_runtime_cancel_pending(struct device *dev)
{
	pm_runtime_deactivate_timer(dev);
	/*
	 * In case there's a request pending, make sure its work function will
	 * return without doing anything.
	 */
	dev->power.request = RPM_REQ_NONE;
}