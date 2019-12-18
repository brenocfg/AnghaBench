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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct mx25_tsadc {int /*<<< orphan*/  domain; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  irq_domain_add_simple (struct device_node*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mx25_tsadc*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct mx25_tsadc*) ; 
 int /*<<< orphan*/  mx25_tsadc_domain_ops ; 
 int /*<<< orphan*/  mx25_tsadc_irq_handler ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mx25_tsadc_setup_irq(struct platform_device *pdev,
				struct mx25_tsadc *tsadc)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	int irq;

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0)
		return irq;

	tsadc->domain = irq_domain_add_simple(np, 2, 0, &mx25_tsadc_domain_ops,
					      tsadc);
	if (!tsadc->domain) {
		dev_err(dev, "Failed to add irq domain\n");
		return -ENOMEM;
	}

	irq_set_chained_handler_and_data(irq, mx25_tsadc_irq_handler, tsadc);

	return 0;
}