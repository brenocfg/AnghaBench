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
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
struct vic {int /*<<< orphan*/  falcon; TYPE_1__ client; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  falcon_exit (int /*<<< orphan*/ *) ; 
 int host1x_client_unregister (int /*<<< orphan*/ *) ; 
 struct vic* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 scalar_t__ pm_runtime_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vic_runtime_suspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vic_remove(struct platform_device *pdev)
{
	struct vic *vic = platform_get_drvdata(pdev);
	int err;

	err = host1x_client_unregister(&vic->client.base);
	if (err < 0) {
		dev_err(&pdev->dev, "failed to unregister host1x client: %d\n",
			err);
		return err;
	}

	if (pm_runtime_enabled(&pdev->dev))
		pm_runtime_disable(&pdev->dev);
	else
		vic_runtime_suspend(&pdev->dev);

	falcon_exit(&vic->falcon);

	return 0;
}