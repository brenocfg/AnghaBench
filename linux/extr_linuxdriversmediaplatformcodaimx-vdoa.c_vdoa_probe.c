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
struct vdoa_data {int /*<<< orphan*/ * dev; int /*<<< orphan*/  regs; int /*<<< orphan*/  vdoa_clk; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct vdoa_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct vdoa_data*) ; 
 int /*<<< orphan*/  dma_set_coherent_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vdoa_data*) ; 
 int /*<<< orphan*/  vdoa_irq_handler ; 

__attribute__((used)) static int vdoa_probe(struct platform_device *pdev)
{
	struct vdoa_data *vdoa;
	struct resource *res;
	int ret;

	dma_set_coherent_mask(&pdev->dev, DMA_BIT_MASK(32));

	vdoa = devm_kzalloc(&pdev->dev, sizeof(*vdoa), GFP_KERNEL);
	if (!vdoa)
		return -ENOMEM;

	vdoa->dev = &pdev->dev;

	vdoa->vdoa_clk = devm_clk_get(vdoa->dev, NULL);
	if (IS_ERR(vdoa->vdoa_clk)) {
		dev_err(vdoa->dev, "Failed to get clock\n");
		return PTR_ERR(vdoa->vdoa_clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	vdoa->regs = devm_ioremap_resource(vdoa->dev, res);
	if (IS_ERR(vdoa->regs))
		return PTR_ERR(vdoa->regs);

	res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);
	if (!res)
		return -EINVAL;
	ret = devm_request_threaded_irq(&pdev->dev, res->start, NULL,
					vdoa_irq_handler, IRQF_ONESHOT,
					"vdoa", vdoa);
	if (ret < 0) {
		dev_err(vdoa->dev, "Failed to get irq\n");
		return ret;
	}

	platform_set_drvdata(pdev, vdoa);

	return 0;
}