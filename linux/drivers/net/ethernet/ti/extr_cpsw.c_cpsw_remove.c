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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int slaves; } ;
struct cpsw_common {int /*<<< orphan*/  dma; int /*<<< orphan*/  cpts; TYPE_2__* slaves; TYPE_1__ data; } ;
struct TYPE_4__ {scalar_t__ ndev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpdma_ctlr_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_remove_dt (struct platform_device*) ; 
 int /*<<< orphan*/  cpts_release (int /*<<< orphan*/ ) ; 
 struct cpsw_common* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (scalar_t__) ; 

__attribute__((used)) static int cpsw_remove(struct platform_device *pdev)
{
	struct cpsw_common *cpsw = platform_get_drvdata(pdev);
	int i, ret;

	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		pm_runtime_put_noidle(&pdev->dev);
		return ret;
	}

	for (i = 0; i < cpsw->data.slaves; i++)
		if (cpsw->slaves[i].ndev)
			unregister_netdev(cpsw->slaves[i].ndev);

	cpts_release(cpsw->cpts);
	cpdma_ctlr_destroy(cpsw->dma);
	cpsw_remove_dt(pdev);
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);
	return 0;
}