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
struct tegra_sor {int /*<<< orphan*/  output; TYPE_1__* ops; int /*<<< orphan*/  client; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* remove ) (struct tegra_sor*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int host1x_client_unregister (int /*<<< orphan*/ *) ; 
 struct tegra_sor* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int stub1 (struct tegra_sor*) ; 
 int /*<<< orphan*/  tegra_output_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_sor_remove(struct platform_device *pdev)
{
	struct tegra_sor *sor = platform_get_drvdata(pdev);
	int err;

	pm_runtime_disable(&pdev->dev);

	err = host1x_client_unregister(&sor->client);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		return err;
	}

	if (sor->ops && sor->ops->remove) {
		err = sor->ops->remove(sor);
		if (err < 0)
			dev_err(&pdev->dev, "failed to remove SOR: %d\n", err);
	}

	tegra_output_remove(&sor->output);

	return 0;
}