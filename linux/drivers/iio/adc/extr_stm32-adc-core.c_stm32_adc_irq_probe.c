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
struct stm32_adc_priv {int* irq; int /*<<< orphan*/  domain; } ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 unsigned int STM32_ADC_MAX_ADCS ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  irq_domain_add_simple (struct device_node*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct stm32_adc_priv*) ; 
 int /*<<< orphan*/  irq_set_chained_handler (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_handler_data (int,struct stm32_adc_priv*) ; 
 int platform_get_irq (struct platform_device*,unsigned int) ; 
 int /*<<< orphan*/  stm32_adc_domain_ops ; 
 int /*<<< orphan*/  stm32_adc_irq_handler ; 

__attribute__((used)) static int stm32_adc_irq_probe(struct platform_device *pdev,
			       struct stm32_adc_priv *priv)
{
	struct device_node *np = pdev->dev.of_node;
	unsigned int i;

	for (i = 0; i < STM32_ADC_MAX_ADCS; i++) {
		priv->irq[i] = platform_get_irq(pdev, i);
		if (priv->irq[i] < 0) {
			/*
			 * At least one interrupt must be provided, make others
			 * optional:
			 * - stm32f4/h7 shares a common interrupt.
			 * - stm32mp1, has one line per ADC (either for ADC1,
			 *   ADC2 or both).
			 */
			if (i && priv->irq[i] == -ENXIO)
				continue;

			return priv->irq[i];
		}
	}

	priv->domain = irq_domain_add_simple(np, STM32_ADC_MAX_ADCS, 0,
					     &stm32_adc_domain_ops,
					     priv);
	if (!priv->domain) {
		dev_err(&pdev->dev, "Failed to add irq domain\n");
		return -ENOMEM;
	}

	for (i = 0; i < STM32_ADC_MAX_ADCS; i++) {
		if (priv->irq[i] < 0)
			continue;
		irq_set_chained_handler(priv->irq[i], stm32_adc_irq_handler);
		irq_set_handler_data(priv->irq[i], priv);
	}

	return 0;
}