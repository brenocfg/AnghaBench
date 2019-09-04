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
struct sh_mtu2_device {scalar_t__ has_clockevent; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ is_early_platform_device (struct platform_device*) ; 
 int /*<<< orphan*/  kfree (struct sh_mtu2_device*) ; 
 struct sh_mtu2_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct sh_mtu2_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_irq_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int sh_mtu2_setup (struct sh_mtu2_device*,struct platform_device*) ; 

__attribute__((used)) static int sh_mtu2_probe(struct platform_device *pdev)
{
	struct sh_mtu2_device *mtu = platform_get_drvdata(pdev);
	int ret;

	if (!is_early_platform_device(pdev)) {
		pm_runtime_set_active(&pdev->dev);
		pm_runtime_enable(&pdev->dev);
	}

	if (mtu) {
		dev_info(&pdev->dev, "kept as earlytimer\n");
		goto out;
	}

	mtu = kzalloc(sizeof(*mtu), GFP_KERNEL);
	if (mtu == NULL)
		return -ENOMEM;

	ret = sh_mtu2_setup(mtu, pdev);
	if (ret) {
		kfree(mtu);
		pm_runtime_idle(&pdev->dev);
		return ret;
	}
	if (is_early_platform_device(pdev))
		return 0;

 out:
	if (mtu->has_clockevent)
		pm_runtime_irq_safe(&pdev->dev);
	else
		pm_runtime_idle(&pdev->dev);

	return 0;
}