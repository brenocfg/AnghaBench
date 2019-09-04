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
struct mtk_cryp {int /*<<< orphan*/  dev; int /*<<< orphan*/  sha_list; int /*<<< orphan*/ * sha; int /*<<< orphan*/ * irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC_ENABLE_SET (size_t) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTK_IRQ_RDR2 ; 
 int /*<<< orphan*/  MTK_IRQ_RDR3 ; 
 size_t MTK_RING2 ; 
 size_t MTK_RING3 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__ mtk_sha ; 
 int /*<<< orphan*/  mtk_sha_irq ; 
 int /*<<< orphan*/  mtk_sha_record_free (struct mtk_cryp*) ; 
 int mtk_sha_record_init (struct mtk_cryp*) ; 
 int mtk_sha_register_algs () ; 
 int /*<<< orphan*/  mtk_sha_write (struct mtk_cryp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mtk_hash_alg_register(struct mtk_cryp *cryp)
{
	int err;

	INIT_LIST_HEAD(&cryp->sha_list);

	/* Initialize two hash records */
	err = mtk_sha_record_init(cryp);
	if (err)
		goto err_record;

	err = devm_request_irq(cryp->dev, cryp->irq[MTK_RING2], mtk_sha_irq,
			       0, "mtk-sha", cryp->sha[0]);
	if (err) {
		dev_err(cryp->dev, "unable to request sha irq0.\n");
		goto err_res;
	}

	err = devm_request_irq(cryp->dev, cryp->irq[MTK_RING3], mtk_sha_irq,
			       0, "mtk-sha", cryp->sha[1]);
	if (err) {
		dev_err(cryp->dev, "unable to request sha irq1.\n");
		goto err_res;
	}

	/* Enable ring2 and ring3 interrupt for hash */
	mtk_sha_write(cryp, AIC_ENABLE_SET(MTK_RING2), MTK_IRQ_RDR2);
	mtk_sha_write(cryp, AIC_ENABLE_SET(MTK_RING3), MTK_IRQ_RDR3);

	spin_lock(&mtk_sha.lock);
	list_add_tail(&cryp->sha_list, &mtk_sha.dev_list);
	spin_unlock(&mtk_sha.lock);

	err = mtk_sha_register_algs();
	if (err)
		goto err_algs;

	return 0;

err_algs:
	spin_lock(&mtk_sha.lock);
	list_del(&cryp->sha_list);
	spin_unlock(&mtk_sha.lock);
err_res:
	mtk_sha_record_free(cryp);
err_record:

	dev_err(cryp->dev, "mtk-sha initialization failed.\n");
	return err;
}