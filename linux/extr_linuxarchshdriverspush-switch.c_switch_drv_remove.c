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
struct push_switch_platform_info {scalar_t__ name; } ;
struct push_switch {int /*<<< orphan*/  debounce; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {struct push_switch_platform_info* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_switch ; 
 int /*<<< orphan*/  device_remove_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int,struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct push_switch*) ; 
 struct push_switch* platform_get_drvdata (struct platform_device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int switch_drv_remove(struct platform_device *pdev)
{
	struct push_switch *psw = platform_get_drvdata(pdev);
	struct push_switch_platform_info *psw_info = pdev->dev.platform_data;
	int irq = platform_get_irq(pdev, 0);

	if (psw_info->name)
		device_remove_file(&pdev->dev, &dev_attr_switch);

	platform_set_drvdata(pdev, NULL);
	flush_work(&psw->work);
	del_timer_sync(&psw->debounce);
	free_irq(irq, pdev);

	kfree(psw);

	return 0;
}