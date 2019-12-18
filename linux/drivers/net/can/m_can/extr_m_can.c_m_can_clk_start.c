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
struct m_can_classdev {scalar_t__ pm_clock_support; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int m_can_clk_start(struct m_can_classdev *cdev)
{
	int err;

	if (cdev->pm_clock_support == 0)
		return 0;

	err = pm_runtime_get_sync(cdev->dev);
	if (err < 0) {
		pm_runtime_put_noidle(cdev->dev);
		return err;
	}

	return 0;
}