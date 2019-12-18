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
struct pl031_local {int dummy; } ;
struct amba_device {scalar_t__* irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 struct pl031_local* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pl031_local*) ; 

__attribute__((used)) static int pl031_remove(struct amba_device *adev)
{
	struct pl031_local *ldata = dev_get_drvdata(&adev->dev);

	dev_pm_clear_wake_irq(&adev->dev);
	device_init_wakeup(&adev->dev, false);
	if (adev->irq[0])
		free_irq(adev->irq[0], ldata);
	amba_release_regions(adev);

	return 0;
}