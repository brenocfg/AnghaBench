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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {scalar_t__ regs; } ;
struct mtk_disp_rdma {int /*<<< orphan*/  data; TYPE_1__ ddp_comp; } ;

/* Variables and functions */
 scalar_t__ DISP_REG_RDMA_INT_ENABLE ; 
 scalar_t__ DISP_REG_RDMA_INT_STATUS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_TRIGGER_NONE ; 
 int /*<<< orphan*/  MTK_DISP_RDMA ; 
 int component_add (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct mtk_disp_rdma* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtk_disp_rdma*) ; 
 int mtk_ddp_comp_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mtk_ddp_comp_init (struct device*,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_disp_rdma_component_ops ; 
 int /*<<< orphan*/  mtk_disp_rdma_funcs ; 
 int /*<<< orphan*/  mtk_disp_rdma_irq_handler ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_disp_rdma*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int mtk_disp_rdma_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mtk_disp_rdma *priv;
	int comp_id;
	int irq;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	comp_id = mtk_ddp_comp_get_id(dev->of_node, MTK_DISP_RDMA);
	if (comp_id < 0) {
		dev_err(dev, "Failed to identify by alias: %d\n", comp_id);
		return comp_id;
	}

	ret = mtk_ddp_comp_init(dev, dev->of_node, &priv->ddp_comp, comp_id,
				&mtk_disp_rdma_funcs);
	if (ret) {
		dev_err(dev, "Failed to initialize component: %d\n", ret);
		return ret;
	}

	/* Disable and clear pending interrupts */
	writel(0x0, priv->ddp_comp.regs + DISP_REG_RDMA_INT_ENABLE);
	writel(0x0, priv->ddp_comp.regs + DISP_REG_RDMA_INT_STATUS);

	ret = devm_request_irq(dev, irq, mtk_disp_rdma_irq_handler,
			       IRQF_TRIGGER_NONE, dev_name(dev), priv);
	if (ret < 0) {
		dev_err(dev, "Failed to request irq %d: %d\n", irq, ret);
		return ret;
	}

	priv->data = of_device_get_match_data(dev);

	platform_set_drvdata(pdev, priv);

	ret = component_add(dev, &mtk_disp_rdma_component_ops);
	if (ret)
		dev_err(dev, "Failed to add component: %d\n", ret);

	return ret;
}