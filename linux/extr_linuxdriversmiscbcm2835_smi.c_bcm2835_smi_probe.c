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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct bcm2835_smi_instance {struct device* dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  smi_regs_busaddr; int /*<<< orphan*/  smi_regs_ptr; int /*<<< orphan*/  transaction_lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int bcm2835_smi_dma_setup (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm2835_smi_instance* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/ * of_get_address (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  smi_setup_regs (struct bcm2835_smi_instance*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_smi_probe(struct platform_device *pdev)
{
	int err;
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct resource *ioresource;
	struct bcm2835_smi_instance *inst;
	const __be32 *addr;

	/* We require device tree support */
	if (!node)
		return -EINVAL;
	/* Allocate buffers and instance data */
	inst = devm_kzalloc(dev, sizeof(struct bcm2835_smi_instance),
		GFP_KERNEL);
	if (!inst)
		return -ENOMEM;

	inst->dev = dev;
	spin_lock_init(&inst->transaction_lock);

	ioresource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	inst->smi_regs_ptr = devm_ioremap_resource(dev, ioresource);
	if (IS_ERR(inst->smi_regs_ptr)) {
		err = PTR_ERR(inst->smi_regs_ptr);
		goto err;
	}
	addr = of_get_address(node, 0, NULL, NULL);
	inst->smi_regs_busaddr = be32_to_cpu(*addr);

	err = bcm2835_smi_dma_setup(inst);
	if (err)
		goto err;

	/* request clock */
	inst->clk = devm_clk_get(dev, NULL);
	if (!inst->clk)
		goto err;
	clk_prepare_enable(inst->clk);

	/* Finally, do peripheral setup */
	smi_setup_regs(inst);

	platform_set_drvdata(pdev, inst);

	dev_info(inst->dev, "initialised");

	return 0;
err:
	kfree(inst);
	return err;
}