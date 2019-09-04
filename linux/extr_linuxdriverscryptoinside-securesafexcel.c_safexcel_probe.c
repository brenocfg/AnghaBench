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
struct safexcel_ring_irq_data {int ring; struct safexcel_crypto_priv* priv; } ;
struct TYPE_4__ {int rings; } ;
struct safexcel_crypto_priv {int version; void* clk; void* reg_clk; int /*<<< orphan*/  ring_used; TYPE_3__* ring; TYPE_1__ config; int /*<<< orphan*/  context_pool; int /*<<< orphan*/  base; int /*<<< orphan*/  flags; struct device* dev; } ;
struct safexcel_context_record {int dummy; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
typedef  enum safexcel_eip_version { ____Placeholder_safexcel_eip_version } safexcel_eip_version ;
struct TYPE_5__ {int ring; int /*<<< orphan*/  work; struct safexcel_crypto_priv* priv; } ;
struct TYPE_6__ {int busy; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; scalar_t__ requests; int /*<<< orphan*/  workqueue; TYPE_2__ work_data; void* rdr_req; int /*<<< orphan*/  rdr; int /*<<< orphan*/  cdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ EIP197B ; 
 scalar_t__ EIP197D ; 
 int EIP197_DEFAULT_RING_SIZE ; 
 int /*<<< orphan*/  EIP197_TRC_CACHE ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  crypto_init_queue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int dma_set_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmam_pool_create (char*,struct device*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_configure (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_dequeue_work ; 
 int safexcel_hw_init (struct safexcel_crypto_priv*) ; 
 int /*<<< orphan*/  safexcel_init_register_offsets (struct safexcel_crypto_priv*) ; 
 int safexcel_init_ring_descriptors (struct safexcel_crypto_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  safexcel_irq_ring ; 
 int /*<<< orphan*/  safexcel_irq_ring_thread ; 
 int safexcel_register_algorithms (struct safexcel_crypto_priv*) ; 
 int safexcel_request_ring_irq (struct platform_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct safexcel_ring_irq_data*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int safexcel_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct safexcel_crypto_priv *priv;
	int i, ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->dev = dev;
	priv->version = (enum safexcel_eip_version)of_device_get_match_data(dev);

	if (priv->version == EIP197B || priv->version == EIP197D)
		priv->flags |= EIP197_TRC_CACHE;

	safexcel_init_register_offsets(priv);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base)) {
		dev_err(dev, "failed to get resource\n");
		return PTR_ERR(priv->base);
	}

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	ret = PTR_ERR_OR_ZERO(priv->clk);
	/* The clock isn't mandatory */
	if  (ret != -ENOENT) {
		if (ret)
			return ret;

		ret = clk_prepare_enable(priv->clk);
		if (ret) {
			dev_err(dev, "unable to enable clk (%d)\n", ret);
			return ret;
		}
	}

	priv->reg_clk = devm_clk_get(&pdev->dev, "reg");
	ret = PTR_ERR_OR_ZERO(priv->reg_clk);
	/* The clock isn't mandatory */
	if  (ret != -ENOENT) {
		if (ret)
			goto err_core_clk;

		ret = clk_prepare_enable(priv->reg_clk);
		if (ret) {
			dev_err(dev, "unable to enable reg clk (%d)\n", ret);
			goto err_core_clk;
		}
	}

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
	if (ret)
		goto err_reg_clk;

	priv->context_pool = dmam_pool_create("safexcel-context", dev,
					      sizeof(struct safexcel_context_record),
					      1, 0);
	if (!priv->context_pool) {
		ret = -ENOMEM;
		goto err_reg_clk;
	}

	safexcel_configure(priv);

	priv->ring = devm_kcalloc(dev, priv->config.rings,
				  sizeof(*priv->ring),
				  GFP_KERNEL);
	if (!priv->ring) {
		ret = -ENOMEM;
		goto err_reg_clk;
	}

	for (i = 0; i < priv->config.rings; i++) {
		char irq_name[6] = {0}; /* "ringX\0" */
		char wq_name[9] = {0}; /* "wq_ringX\0" */
		int irq;
		struct safexcel_ring_irq_data *ring_irq;

		ret = safexcel_init_ring_descriptors(priv,
						     &priv->ring[i].cdr,
						     &priv->ring[i].rdr);
		if (ret)
			goto err_reg_clk;

		priv->ring[i].rdr_req = devm_kcalloc(dev,
			EIP197_DEFAULT_RING_SIZE,
			sizeof(priv->ring[i].rdr_req),
			GFP_KERNEL);
		if (!priv->ring[i].rdr_req) {
			ret = -ENOMEM;
			goto err_reg_clk;
		}

		ring_irq = devm_kzalloc(dev, sizeof(*ring_irq), GFP_KERNEL);
		if (!ring_irq) {
			ret = -ENOMEM;
			goto err_reg_clk;
		}

		ring_irq->priv = priv;
		ring_irq->ring = i;

		snprintf(irq_name, 6, "ring%d", i);
		irq = safexcel_request_ring_irq(pdev, irq_name, safexcel_irq_ring,
						safexcel_irq_ring_thread,
						ring_irq);
		if (irq < 0) {
			ret = irq;
			goto err_reg_clk;
		}

		priv->ring[i].work_data.priv = priv;
		priv->ring[i].work_data.ring = i;
		INIT_WORK(&priv->ring[i].work_data.work, safexcel_dequeue_work);

		snprintf(wq_name, 9, "wq_ring%d", i);
		priv->ring[i].workqueue = create_singlethread_workqueue(wq_name);
		if (!priv->ring[i].workqueue) {
			ret = -ENOMEM;
			goto err_reg_clk;
		}

		priv->ring[i].requests = 0;
		priv->ring[i].busy = false;

		crypto_init_queue(&priv->ring[i].queue,
				  EIP197_DEFAULT_RING_SIZE);

		spin_lock_init(&priv->ring[i].lock);
		spin_lock_init(&priv->ring[i].queue_lock);
	}

	platform_set_drvdata(pdev, priv);
	atomic_set(&priv->ring_used, 0);

	ret = safexcel_hw_init(priv);
	if (ret) {
		dev_err(dev, "EIP h/w init failed (%d)\n", ret);
		goto err_reg_clk;
	}

	ret = safexcel_register_algorithms(priv);
	if (ret) {
		dev_err(dev, "Failed to register algorithms (%d)\n", ret);
		goto err_reg_clk;
	}

	return 0;

err_reg_clk:
	clk_disable_unprepare(priv->reg_clk);
err_core_clk:
	clk_disable_unprepare(priv->clk);
	return ret;
}