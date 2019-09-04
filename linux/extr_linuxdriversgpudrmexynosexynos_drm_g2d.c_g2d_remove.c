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
struct g2d_data {int /*<<< orphan*/  runqueue_slab; int /*<<< orphan*/  g2d_workq; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g2d_component_ops ; 
 int /*<<< orphan*/  g2d_fini_cmdlist (struct g2d_data*) ; 
 int /*<<< orphan*/  g2d_remove_runqueue_nodes (struct g2d_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 struct g2d_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int g2d_remove(struct platform_device *pdev)
{
	struct g2d_data *g2d = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &g2d_component_ops);

	/* There should be no locking needed here. */
	g2d_remove_runqueue_nodes(g2d, NULL);

	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	g2d_fini_cmdlist(g2d);
	destroy_workqueue(g2d->g2d_workq);
	kmem_cache_destroy(g2d->runqueue_slab);

	return 0;
}