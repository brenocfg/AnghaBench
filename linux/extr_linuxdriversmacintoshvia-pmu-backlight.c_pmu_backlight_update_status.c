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
struct backlight_device {int dummy; } ;

/* Variables and functions */
 int __pmu_backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  pmu_backlight_lock ; 
 int /*<<< orphan*/  sleeping ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pmu_backlight_update_status(struct backlight_device *bd)
{
	unsigned long flags;
	int rc = 0;

	spin_lock_irqsave(&pmu_backlight_lock, flags);
	/* Don't update brightness when sleeping */
	if (!sleeping)
		rc = __pmu_backlight_update_status(bd);
	spin_unlock_irqrestore(&pmu_backlight_lock, flags);
	return rc;
}