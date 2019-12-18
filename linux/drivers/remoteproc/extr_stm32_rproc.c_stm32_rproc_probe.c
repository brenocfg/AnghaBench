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
struct stm32_rproc {int dummy; } ;
struct rproc {int has_iommu; struct stm32_rproc* priv; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int ENOMEM ; 
 int dma_coerce_mask_and_coherent (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rproc*) ; 
 int rproc_add (struct rproc*) ; 
 struct rproc* rproc_alloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rproc_free (struct rproc*) ; 
 int /*<<< orphan*/  st_rproc_ops ; 
 int /*<<< orphan*/  stm32_rproc_free_mbox (struct rproc*) ; 
 int stm32_rproc_parse_dt (struct platform_device*) ; 
 int /*<<< orphan*/  stm32_rproc_request_mbox (struct rproc*) ; 

__attribute__((used)) static int stm32_rproc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct stm32_rproc *ddata;
	struct device_node *np = dev->of_node;
	struct rproc *rproc;
	int ret;

	ret = dma_coerce_mask_and_coherent(dev, DMA_BIT_MASK(32));
	if (ret)
		return ret;

	rproc = rproc_alloc(dev, np->name, &st_rproc_ops, NULL, sizeof(*ddata));
	if (!rproc)
		return -ENOMEM;

	rproc->has_iommu = false;
	ddata = rproc->priv;

	platform_set_drvdata(pdev, rproc);

	ret = stm32_rproc_parse_dt(pdev);
	if (ret)
		goto free_rproc;

	stm32_rproc_request_mbox(rproc);

	ret = rproc_add(rproc);
	if (ret)
		goto free_mb;

	return 0;

free_mb:
	stm32_rproc_free_mbox(rproc);
free_rproc:
	rproc_free(rproc);
	return ret;
}