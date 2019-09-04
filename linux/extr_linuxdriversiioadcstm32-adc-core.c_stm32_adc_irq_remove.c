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
struct stm32_adc_priv {scalar_t__* irq; int /*<<< orphan*/  domain; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int STM32_ADC_MAX_ADCS ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_adc_irq_remove(struct platform_device *pdev,
				 struct stm32_adc_priv *priv)
{
	int hwirq;
	unsigned int i;

	for (hwirq = 0; hwirq < STM32_ADC_MAX_ADCS; hwirq++)
		irq_dispose_mapping(irq_find_mapping(priv->domain, hwirq));
	irq_domain_remove(priv->domain);

	for (i = 0; i < STM32_ADC_MAX_ADCS; i++) {
		if (priv->irq[i] < 0)
			continue;
		irq_set_chained_handler(priv->irq[i], NULL);
	}
}