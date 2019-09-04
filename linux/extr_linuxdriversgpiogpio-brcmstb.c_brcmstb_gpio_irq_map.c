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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct irq_domain {struct brcmstb_gpio_priv* host_data; } ;
struct brcmstb_gpio_priv {int /*<<< orphan*/  irq_chip; struct platform_device* pdev; } ;
struct brcmstb_gpio_bank {int /*<<< orphan*/  gc; int /*<<< orphan*/  id; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int EINVAL ; 
 struct brcmstb_gpio_bank* brcmstb_gpio_hwirq_to_bank (struct brcmstb_gpio_priv*,scalar_t__) ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_lock_class ; 
 int /*<<< orphan*/  brcmstb_gpio_irq_request_class ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int irq_set_chip_data (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_lockdep_class (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_noprobe (unsigned int) ; 

__attribute__((used)) static int brcmstb_gpio_irq_map(struct irq_domain *d, unsigned int irq,
		irq_hw_number_t hwirq)
{
	struct brcmstb_gpio_priv *priv = d->host_data;
	struct brcmstb_gpio_bank *bank =
		brcmstb_gpio_hwirq_to_bank(priv, hwirq);
	struct platform_device *pdev = priv->pdev;
	int ret;

	if (!bank)
		return -EINVAL;

	dev_dbg(&pdev->dev, "Mapping irq %d for gpio line %d (bank %d)\n",
		irq, (int)hwirq, bank->id);
	ret = irq_set_chip_data(irq, &bank->gc);
	if (ret < 0)
		return ret;
	irq_set_lockdep_class(irq, &brcmstb_gpio_irq_lock_class,
			      &brcmstb_gpio_irq_request_class);
	irq_set_chip_and_handler(irq, &priv->irq_chip, handle_level_irq);
	irq_set_noprobe(irq);
	return 0;
}