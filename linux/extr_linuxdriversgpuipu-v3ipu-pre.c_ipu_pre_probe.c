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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct ipu_pre {int /*<<< orphan*/  list; struct device* dev; int /*<<< orphan*/  clk_axi; int /*<<< orphan*/  buffer_virt; int /*<<< orphan*/  buffer_paddr; int /*<<< orphan*/  iram; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int IPU_PRE_MAX_WIDTH ; 
 int IPU_PRE_NUM_SCANLINES ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  available_pres ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ipu_pre* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool_dma_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_pre_list ; 
 int /*<<< orphan*/  ipu_pre_list_mutex ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_gen_pool_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ipu_pre*) ; 

__attribute__((used)) static int ipu_pre_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct ipu_pre *pre;

	pre = devm_kzalloc(dev, sizeof(*pre), GFP_KERNEL);
	if (!pre)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pre->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pre->regs))
		return PTR_ERR(pre->regs);

	pre->clk_axi = devm_clk_get(dev, "axi");
	if (IS_ERR(pre->clk_axi))
		return PTR_ERR(pre->clk_axi);

	pre->iram = of_gen_pool_get(dev->of_node, "fsl,iram", 0);
	if (!pre->iram)
		return -EPROBE_DEFER;

	/*
	 * Allocate IRAM buffer with maximum size. This could be made dynamic,
	 * but as there is no other user of this IRAM region and we can fit all
	 * max sized buffers into it, there is no need yet.
	 */
	pre->buffer_virt = gen_pool_dma_alloc(pre->iram, IPU_PRE_MAX_WIDTH *
					      IPU_PRE_NUM_SCANLINES * 4,
					      &pre->buffer_paddr);
	if (!pre->buffer_virt)
		return -ENOMEM;

	clk_prepare_enable(pre->clk_axi);

	pre->dev = dev;
	platform_set_drvdata(pdev, pre);
	mutex_lock(&ipu_pre_list_mutex);
	list_add(&pre->list, &ipu_pre_list);
	available_pres++;
	mutex_unlock(&ipu_pre_list_mutex);

	return 0;
}