#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct irq_chip {int /*<<< orphan*/  irq_eoi; int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  name; } ;
struct mvebu_pic {scalar_t__ parent_irq; int /*<<< orphan*/  domain; struct irq_chip irq_chip; int /*<<< orphan*/  base; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC_MAX_IRQS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct mvebu_pic* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvebu_pic*) ; 
 scalar_t__ irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_handler_data (scalar_t__,struct mvebu_pic*) ; 
 int /*<<< orphan*/  mvebu_pic_domain_ops ; 
 int /*<<< orphan*/  mvebu_pic_enable_percpu_irq ; 
 int /*<<< orphan*/  mvebu_pic_eoi_irq ; 
 int /*<<< orphan*/  mvebu_pic_handle_cascade_irq ; 
 int /*<<< orphan*/  mvebu_pic_mask_irq ; 
 int /*<<< orphan*/  mvebu_pic_unmask_irq ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,struct mvebu_pic*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mvebu_pic*) ; 

__attribute__((used)) static int mvebu_pic_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct mvebu_pic *pic;
	struct irq_chip *irq_chip;
	struct resource *res;

	pic = devm_kzalloc(&pdev->dev, sizeof(struct mvebu_pic), GFP_KERNEL);
	if (!pic)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pic->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pic->base))
		return PTR_ERR(pic->base);

	irq_chip = &pic->irq_chip;
	irq_chip->name = dev_name(&pdev->dev);
	irq_chip->irq_mask = mvebu_pic_mask_irq;
	irq_chip->irq_unmask = mvebu_pic_unmask_irq;
	irq_chip->irq_eoi = mvebu_pic_eoi_irq;

	pic->parent_irq = irq_of_parse_and_map(node, 0);
	if (pic->parent_irq <= 0) {
		dev_err(&pdev->dev, "Failed to parse parent interrupt\n");
		return -EINVAL;
	}

	pic->domain = irq_domain_add_linear(node, PIC_MAX_IRQS,
					    &mvebu_pic_domain_ops, pic);
	if (!pic->domain) {
		dev_err(&pdev->dev, "Failed to allocate irq domain\n");
		return -ENOMEM;
	}

	irq_set_chained_handler(pic->parent_irq, mvebu_pic_handle_cascade_irq);
	irq_set_handler_data(pic->parent_irq, pic);

	on_each_cpu(mvebu_pic_enable_percpu_irq, pic, 1);

	platform_set_drvdata(pdev, pic);

	return 0;
}