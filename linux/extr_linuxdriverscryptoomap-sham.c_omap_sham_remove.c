#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_sham_dev {int /*<<< orphan*/  dma_lch; int /*<<< orphan*/  polling_mode; int /*<<< orphan*/  done_task; TYPE_2__* pdata; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int algs_info_size; TYPE_1__* algs_info; } ;
struct TYPE_4__ {int registered; int /*<<< orphan*/ * algs_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  crypto_unregister_ahash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct omap_sham_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 TYPE_3__ sham ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_sham_remove(struct platform_device *pdev)
{
	struct omap_sham_dev *dd;
	int i, j;

	dd = platform_get_drvdata(pdev);
	if (!dd)
		return -ENODEV;
	spin_lock(&sham.lock);
	list_del(&dd->list);
	spin_unlock(&sham.lock);
	for (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		for (j = dd->pdata->algs_info[i].registered - 1; j >= 0; j--)
			crypto_unregister_ahash(
					&dd->pdata->algs_info[i].algs_list[j]);
	tasklet_kill(&dd->done_task);
	pm_runtime_disable(&pdev->dev);

	if (!dd->polling_mode)
		dma_release_channel(dd->dma_lch);

	return 0;
}