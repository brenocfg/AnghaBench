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
struct mtk_cryp {int /*<<< orphan*/  dev; int /*<<< orphan*/  aes_list; int /*<<< orphan*/ * aes; int /*<<< orphan*/ * irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC_ENABLE_SET (size_t) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTK_IRQ_RDR0 ; 
 int /*<<< orphan*/  MTK_IRQ_RDR1 ; 
 size_t MTK_RING0 ; 
 size_t MTK_RING1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 TYPE_1__ mtk_aes ; 
 int /*<<< orphan*/  mtk_aes_irq ; 
 int /*<<< orphan*/  mtk_aes_record_free (struct mtk_cryp*) ; 
 int mtk_aes_record_init (struct mtk_cryp*) ; 
 int mtk_aes_register_algs () ; 
 int /*<<< orphan*/  mtk_aes_write (struct mtk_cryp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int mtk_cipher_alg_register(struct mtk_cryp *cryp)
{
	int ret;

	INIT_LIST_HEAD(&cryp->aes_list);

	/* Initialize two cipher records */
	ret = mtk_aes_record_init(cryp);
	if (ret)
		goto err_record;

	ret = devm_request_irq(cryp->dev, cryp->irq[MTK_RING0], mtk_aes_irq,
			       0, "mtk-aes", cryp->aes[0]);
	if (ret) {
		dev_err(cryp->dev, "unable to request AES irq.\n");
		goto err_res;
	}

	ret = devm_request_irq(cryp->dev, cryp->irq[MTK_RING1], mtk_aes_irq,
			       0, "mtk-aes", cryp->aes[1]);
	if (ret) {
		dev_err(cryp->dev, "unable to request AES irq.\n");
		goto err_res;
	}

	/* Enable ring0 and ring1 interrupt */
	mtk_aes_write(cryp, AIC_ENABLE_SET(MTK_RING0), MTK_IRQ_RDR0);
	mtk_aes_write(cryp, AIC_ENABLE_SET(MTK_RING1), MTK_IRQ_RDR1);

	spin_lock(&mtk_aes.lock);
	list_add_tail(&cryp->aes_list, &mtk_aes.dev_list);
	spin_unlock(&mtk_aes.lock);

	ret = mtk_aes_register_algs();
	if (ret)
		goto err_algs;

	return 0;

err_algs:
	spin_lock(&mtk_aes.lock);
	list_del(&cryp->aes_list);
	spin_unlock(&mtk_aes.lock);
err_res:
	mtk_aes_record_free(cryp);
err_record:

	dev_err(cryp->dev, "mtk-aes initialization failed.\n");
	return ret;
}