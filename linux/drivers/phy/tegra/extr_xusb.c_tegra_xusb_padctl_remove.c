#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_xusb_padctl {TYPE_2__* soc; int /*<<< orphan*/  rst; int /*<<< orphan*/  supplies; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  num_supplies; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* remove ) (struct tegra_xusb_padctl*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct tegra_xusb_padctl* platform_get_drvdata (struct platform_device*) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  tegra_xusb_remove_pads (struct tegra_xusb_padctl*) ; 
 int /*<<< orphan*/  tegra_xusb_remove_ports (struct tegra_xusb_padctl*) ; 

__attribute__((used)) static int tegra_xusb_padctl_remove(struct platform_device *pdev)
{
	struct tegra_xusb_padctl *padctl = platform_get_drvdata(pdev);
	int err;

	tegra_xusb_remove_ports(padctl);
	tegra_xusb_remove_pads(padctl);

	err = regulator_bulk_disable(padctl->soc->num_supplies,
				     padctl->supplies);
	if (err < 0)
		dev_err(&pdev->dev, "failed to disable supplies: %d\n", err);

	err = reset_control_assert(padctl->rst);
	if (err < 0)
		dev_err(&pdev->dev, "failed to assert reset: %d\n", err);

	padctl->soc->ops->remove(padctl);

	return err;
}