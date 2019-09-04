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
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct mtk_mdp_dev {int /*<<< orphan*/ * comp; int /*<<< orphan*/  job_wq; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_comp_deinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_mdp_unregister_m2m_device (struct mtk_mdp_dev*) ; 
 struct mtk_mdp_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mtk_mdp_remove(struct platform_device *pdev)
{
	struct mtk_mdp_dev *mdp = platform_get_drvdata(pdev);
	int i;

	pm_runtime_disable(&pdev->dev);
	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	mtk_mdp_unregister_m2m_device(mdp);
	v4l2_device_unregister(&mdp->v4l2_dev);

	flush_workqueue(mdp->job_wq);
	destroy_workqueue(mdp->job_wq);

	for (i = 0; i < ARRAY_SIZE(mdp->comp); i++)
		mtk_mdp_comp_deinit(&pdev->dev, mdp->comp[i]);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);
	return 0;
}