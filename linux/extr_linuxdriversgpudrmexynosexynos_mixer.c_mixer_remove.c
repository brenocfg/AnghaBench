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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mixer_component_ops ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mixer_remove(struct platform_device *pdev)
{
	pm_runtime_disable(&pdev->dev);

	component_del(&pdev->dev, &mixer_component_ops);

	return 0;
}