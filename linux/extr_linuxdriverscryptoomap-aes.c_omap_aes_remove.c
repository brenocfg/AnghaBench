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
struct platform_device {int dummy; } ;
struct omap_aes_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  done_task; int /*<<< orphan*/  engine; TYPE_3__* pdata; int /*<<< orphan*/  list; } ;
struct aead_alg {int dummy; } ;
struct TYPE_6__ {int algs_info_size; TYPE_2__* aead_algs_info; TYPE_1__* algs_info; } ;
struct TYPE_5__ {int size; struct aead_alg* algs_list; } ;
struct TYPE_4__ {int registered; int /*<<< orphan*/ * algs_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  crypto_engine_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_unregister_aead (struct aead_alg*) ; 
 int /*<<< orphan*/  crypto_unregister_alg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lock ; 
 int /*<<< orphan*/  omap_aes_dma_cleanup (struct omap_aes_dev*) ; 
 struct omap_aes_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_aes_remove(struct platform_device *pdev)
{
	struct omap_aes_dev *dd = platform_get_drvdata(pdev);
	struct aead_alg *aalg;
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

	for (i = dd->pdata->aead_algs_info->size - 1; i >= 0; i--) {
		aalg = &dd->pdata->aead_algs_info->algs_list[i];
		crypto_unregister_aead(aalg);
	}

	crypto_engine_exit(dd->engine);

	tasklet_kill(&dd->done_task);
	omap_aes_dma_cleanup(dd);
	pm_runtime_disable(dd->dev);
	dd = NULL;

	return 0;
}