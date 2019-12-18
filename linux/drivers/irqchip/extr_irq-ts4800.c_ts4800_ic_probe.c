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
struct irq_chip {int /*<<< orphan*/  irq_unmask; int /*<<< orphan*/  irq_mask; int /*<<< orphan*/  name; } ;
struct ts4800_irq_data {int /*<<< orphan*/  domain; struct irq_chip irq_chip; scalar_t__ base; } ;
struct resource {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IRQ_MASK ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 scalar_t__ devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct ts4800_irq_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (struct device_node*,int,int /*<<< orphan*/ *,struct ts4800_irq_data*) ; 
 int irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct ts4800_irq_data*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ts4800_irq_data*) ; 
 int /*<<< orphan*/  ts4800_ic_chained_handle_irq ; 
 int /*<<< orphan*/  ts4800_ic_ops ; 
 int /*<<< orphan*/  ts4800_irq_mask ; 
 int /*<<< orphan*/  ts4800_irq_unmask ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ts4800_ic_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	struct ts4800_irq_data *data;
	struct irq_chip *irq_chip;
	struct resource *res;
	int parent_irq;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	writew(0xFFFF, data->base + IRQ_MASK);

	parent_irq = irq_of_parse_and_map(node, 0);
	if (!parent_irq) {
		dev_err(&pdev->dev, "failed to get parent IRQ\n");
		return -EINVAL;
	}

	irq_chip = &data->irq_chip;
	irq_chip->name = dev_name(&pdev->dev);
	irq_chip->irq_mask = ts4800_irq_mask;
	irq_chip->irq_unmask = ts4800_irq_unmask;

	data->domain = irq_domain_add_linear(node, 8, &ts4800_ic_ops, data);
	if (!data->domain) {
		dev_err(&pdev->dev, "cannot add IRQ domain\n");
		return -ENOMEM;
	}

	irq_set_chained_handler_and_data(parent_irq,
					 ts4800_ic_chained_handle_irq, data);

	platform_set_drvdata(pdev, data);

	return 0;
}