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
typedef  int /*<<< orphan*/  u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ast_vhub {int force_usb1; int irq; int /*<<< orphan*/  ep0; scalar_t__ ep0_bufs_dma; int /*<<< orphan*/  ep0_bufs; scalar_t__ regs; scalar_t__ clk; struct platform_device* pdev; int /*<<< orphan*/  lock; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;

/* Variables and functions */
 int AST_VHUB_EP0_MAX_PACKET ; 
 scalar_t__ AST_VHUB_IER ; 
 scalar_t__ AST_VHUB_ISR ; 
 int AST_VHUB_NUM_PORTS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  UDCDBG (struct ast_vhub*,char*,struct resource*,scalar_t__) ; 
 int /*<<< orphan*/  UDCVDBG (struct ast_vhub*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int USB_SPEED_HIGH ; 
 int USB_SPEED_UNKNOWN ; 
 int /*<<< orphan*/  VHUB_IRQ_ACK_ALL ; 
 int ast_vhub_init_dev (struct ast_vhub*,int) ; 
 int /*<<< orphan*/  ast_vhub_init_ep0 (struct ast_vhub*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ast_vhub_init_hub (struct ast_vhub*) ; 
 int /*<<< orphan*/  ast_vhub_init_hw (struct ast_vhub*) ; 
 int /*<<< orphan*/  ast_vhub_irq ; 
 int /*<<< orphan*/  ast_vhub_remove (struct platform_device*) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct ast_vhub* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ast_vhub*) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ast_vhub*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int usb_get_maximum_speed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ast_vhub_probe(struct platform_device *pdev)
{
	enum usb_device_speed max_speed;
	struct ast_vhub *vhub;
	struct resource *res;
	int i, rc = 0;

	vhub = devm_kzalloc(&pdev->dev, sizeof(*vhub), GFP_KERNEL);
	if (!vhub)
		return -ENOMEM;

	spin_lock_init(&vhub->lock);
	vhub->pdev = pdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vhub->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(vhub->regs)) {
		dev_err(&pdev->dev, "Failed to map resources\n");
		return PTR_ERR(vhub->regs);
	}
	UDCDBG(vhub, "vHub@%pR mapped @%p\n", res, vhub->regs);

	platform_set_drvdata(pdev, vhub);

	vhub->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(vhub->clk)) {
		rc = PTR_ERR(vhub->clk);
		goto err;
	}
	rc = clk_prepare_enable(vhub->clk);
	if (rc) {
		dev_err(&pdev->dev, "Error couldn't enable clock (%d)\n", rc);
		goto err;
	}

	/* Check if we need to limit the HW to USB1 */
	max_speed = usb_get_maximum_speed(&pdev->dev);
	if (max_speed != USB_SPEED_UNKNOWN && max_speed < USB_SPEED_HIGH)
		vhub->force_usb1 = true;

	/* Mask & ack all interrupts before installing the handler */
	writel(0, vhub->regs + AST_VHUB_IER);
	writel(VHUB_IRQ_ACK_ALL, vhub->regs + AST_VHUB_ISR);

	/* Find interrupt and install handler */
	vhub->irq = platform_get_irq(pdev, 0);
	if (vhub->irq < 0) {
		rc = vhub->irq;
		goto err;
	}
	rc = devm_request_irq(&pdev->dev, vhub->irq, ast_vhub_irq, 0,
			      KBUILD_MODNAME, vhub);
	if (rc) {
		dev_err(&pdev->dev, "Failed to request interrupt\n");
		goto err;
	}

	/*
	 * Allocate DMA buffers for all EP0s in one chunk,
	 * one per port and one for the vHub itself
	 */
	vhub->ep0_bufs = dma_alloc_coherent(&pdev->dev,
					    AST_VHUB_EP0_MAX_PACKET *
					    (AST_VHUB_NUM_PORTS + 1),
					    &vhub->ep0_bufs_dma, GFP_KERNEL);
	if (!vhub->ep0_bufs) {
		dev_err(&pdev->dev, "Failed to allocate EP0 DMA buffers\n");
		rc = -ENOMEM;
		goto err;
	}
	UDCVDBG(vhub, "EP0 DMA buffers @%p (DMA 0x%08x)\n",
		vhub->ep0_bufs, (u32)vhub->ep0_bufs_dma);

	/* Init vHub EP0 */
	ast_vhub_init_ep0(vhub, &vhub->ep0, NULL);

	/* Init devices */
	for (i = 0; i < AST_VHUB_NUM_PORTS && rc == 0; i++)
		rc = ast_vhub_init_dev(vhub, i);
	if (rc)
		goto err;

	/* Init hub emulation */
	ast_vhub_init_hub(vhub);

	/* Initialize HW */
	ast_vhub_init_hw(vhub);

	dev_info(&pdev->dev, "Initialized virtual hub in USB%d mode\n",
		 vhub->force_usb1 ? 1 : 2);

	return 0;
 err:
	ast_vhub_remove(pdev);
	return rc;
}