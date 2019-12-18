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

/* Variables and functions */
 int /*<<< orphan*/  component_del (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  scaler_component_ops ; 

__attribute__((used)) static int scaler_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	component_del(dev, &scaler_component_ops);
	pm_runtime_dont_use_autosuspend(dev);
	pm_runtime_disable(dev);

	return 0;
}