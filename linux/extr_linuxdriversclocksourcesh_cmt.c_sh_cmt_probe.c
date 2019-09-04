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
struct sh_cmt_device {scalar_t__ has_clocksource; scalar_t__ has_clockevent; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_early_platform_device (struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct sh_cmt_device*) ; 
 struct sh_cmt_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sh_cmt_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_irq_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int sh_cmt_setup (struct sh_cmt_device*,struct platform_device*) ; 

__attribute__((used)) static int sh_cmt_probe(struct platform_device *pdev)
{
	struct sh_cmt_device *cmt = platform_get_drvdata(pdev);
	int ret;

	if (!is_early_platform_device(pdev)) {
		pm_runtime_set_active(&pdev->dev);
		pm_runtime_enable(&pdev->dev);
	}

	if (cmt) {
		dev_info(&pdev->dev, "kept as earlytimer\n");
		goto out;
	}

	cmt = kzalloc(sizeof(*cmt), GFP_KERNEL);
	if (cmt == NULL)
		return -ENOMEM;

	ret = sh_cmt_setup(cmt, pdev);
	if (ret) {
		kfree(cmt);
		pm_runtime_idle(&pdev->dev);
		return ret;
	}
	if (is_early_platform_device(pdev))
		return 0;

 out:
	if (cmt->has_clockevent || cmt->has_clocksource)
		pm_runtime_irq_safe(&pdev->dev);
	else
		pm_runtime_idle(&pdev->dev);

	return 0;
}