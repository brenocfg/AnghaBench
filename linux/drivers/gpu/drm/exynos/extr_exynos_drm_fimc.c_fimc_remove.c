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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct fimc_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_component_ops ; 
 int /*<<< orphan*/  fimc_put_clocks (struct fimc_context*) ; 
 struct fimc_context* get_fimc_context (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 

__attribute__((used)) static int fimc_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fimc_context *ctx = get_fimc_context(dev);

	component_del(dev, &fimc_component_ops);
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);

	fimc_put_clocks(ctx);

	return 0;
}