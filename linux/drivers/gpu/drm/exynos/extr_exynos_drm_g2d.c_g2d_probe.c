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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct g2d_runqueue_node {int dummy; } ;
struct g2d_data {int irq; int /*<<< orphan*/  runqueue_slab; int /*<<< orphan*/  g2d_workq; int /*<<< orphan*/  max_pool; int /*<<< orphan*/  regs; int /*<<< orphan*/  flags; int /*<<< orphan*/  gate_clk; int /*<<< orphan*/  runqueue_mutex; int /*<<< orphan*/  cmdlist_mutex; int /*<<< orphan*/  runqueue; int /*<<< orphan*/  free_cmdlist; int /*<<< orphan*/  runqueue_work; struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  G2D_BIT_ENGINE_BUSY ; 
 int /*<<< orphan*/  G2D_BIT_SUSPEND_RUNQUEUE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_POOL ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct g2d_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct g2d_data*) ; 
 int /*<<< orphan*/  g2d_component_ops ; 
 int /*<<< orphan*/  g2d_irq_handler ; 
 int /*<<< orphan*/  g2d_runqueue_worker ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct g2d_data*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

__attribute__((used)) static int g2d_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct g2d_data *g2d;
	int ret;

	g2d = devm_kzalloc(dev, sizeof(*g2d), GFP_KERNEL);
	if (!g2d)
		return -ENOMEM;

	g2d->runqueue_slab = kmem_cache_create("g2d_runqueue_slab",
			sizeof(struct g2d_runqueue_node), 0, 0, NULL);
	if (!g2d->runqueue_slab)
		return -ENOMEM;

	g2d->dev = dev;

	g2d->g2d_workq = create_singlethread_workqueue("g2d");
	if (!g2d->g2d_workq) {
		dev_err(dev, "failed to create workqueue\n");
		ret = -EINVAL;
		goto err_destroy_slab;
	}

	INIT_WORK(&g2d->runqueue_work, g2d_runqueue_worker);
	INIT_LIST_HEAD(&g2d->free_cmdlist);
	INIT_LIST_HEAD(&g2d->runqueue);

	mutex_init(&g2d->cmdlist_mutex);
	mutex_init(&g2d->runqueue_mutex);

	g2d->gate_clk = devm_clk_get(dev, "fimg2d");
	if (IS_ERR(g2d->gate_clk)) {
		dev_err(dev, "failed to get gate clock\n");
		ret = PTR_ERR(g2d->gate_clk);
		goto err_destroy_workqueue;
	}

	pm_runtime_use_autosuspend(dev);
	pm_runtime_set_autosuspend_delay(dev, 2000);
	pm_runtime_enable(dev);
	clear_bit(G2D_BIT_SUSPEND_RUNQUEUE, &g2d->flags);
	clear_bit(G2D_BIT_ENGINE_BUSY, &g2d->flags);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	g2d->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(g2d->regs)) {
		ret = PTR_ERR(g2d->regs);
		goto err_put_clk;
	}

	g2d->irq = platform_get_irq(pdev, 0);
	if (g2d->irq < 0) {
		dev_err(dev, "failed to get irq\n");
		ret = g2d->irq;
		goto err_put_clk;
	}

	ret = devm_request_irq(dev, g2d->irq, g2d_irq_handler, 0,
								"drm_g2d", g2d);
	if (ret < 0) {
		dev_err(dev, "irq request failed\n");
		goto err_put_clk;
	}

	g2d->max_pool = MAX_POOL;

	platform_set_drvdata(pdev, g2d);

	ret = component_add(dev, &g2d_component_ops);
	if (ret < 0) {
		dev_err(dev, "failed to register drm g2d device\n");
		goto err_put_clk;
	}

	return 0;

err_put_clk:
	pm_runtime_disable(dev);
err_destroy_workqueue:
	destroy_workqueue(g2d->g2d_workq);
err_destroy_slab:
	kmem_cache_destroy(g2d->runqueue_slab);
	return ret;
}