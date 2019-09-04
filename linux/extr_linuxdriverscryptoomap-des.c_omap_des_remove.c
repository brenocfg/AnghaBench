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
struct platform_device {int dummy; } ;
struct omap_des_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  done_task; TYPE_2__* pdata; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int algs_info_size; TYPE_1__* algs_info; } ;
struct TYPE_3__ {int registered; int /*<<< orphan*/ * algs_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  omap_des_dma_cleanup (struct omap_des_dev*) ; 
 struct omap_des_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_des_remove(struct platform_device *pdev)
{
	struct omap_des_dev *dd = platform_get_drvdata(pdev);
	int i, j;

	if (!dd)
		return -ENODEV;

	spin_lock(&list_lock);
	list_del(&dd->list);
	spin_unlock(&list_lock);

	for (i = dd->pdata->algs_info_size - 1; i >= 0; i--)
		for (j = dd->pdata->algs_info[i].registered - 1; j >= 0; j--)
			crypto_unregister_alg(
					&dd->pdata->algs_info[i].algs_list[j]);

	tasklet_kill(&dd->done_task);
	omap_des_dma_cleanup(dd);
	pm_runtime_disable(dd->dev);
	dd = NULL;

	return 0;
}