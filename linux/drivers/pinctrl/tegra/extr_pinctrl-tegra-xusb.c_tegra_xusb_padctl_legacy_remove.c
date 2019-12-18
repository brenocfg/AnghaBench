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
struct tegra_xusb_padctl {int /*<<< orphan*/  rst; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct tegra_xusb_padctl* platform_get_drvdata (struct platform_device*) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 

int tegra_xusb_padctl_legacy_remove(struct platform_device *pdev)
{
	struct tegra_xusb_padctl *padctl = platform_get_drvdata(pdev);
	int err;

	err = reset_control_assert(padctl->rst);
	if (err < 0)
		dev_err(&pdev->dev, "failed to assert reset: %d\n", err);

	return err;
}