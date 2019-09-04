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
struct omap_dm_timer {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __omap_dm_timer_write_status (struct omap_dm_timer*,unsigned int) ; 
 scalar_t__ pm_runtime_suspended (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int omap_dm_timer_write_status(struct omap_dm_timer *timer, unsigned int value)
{
	if (unlikely(!timer || pm_runtime_suspended(&timer->pdev->dev)))
		return -EINVAL;

	__omap_dm_timer_write_status(timer, value);

	return 0;
}