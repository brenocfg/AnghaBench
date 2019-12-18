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
typedef  scalar_t__ u32 ;
struct xgene_gpio_sb {scalar_t__ irq_start; int /*<<< orphan*/  nirq; } ;
struct irq_fwspec {int param_count; int /*<<< orphan*/ * param; int /*<<< orphan*/  fwnode; } ;
struct gpio_chip {TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_TO_HWIRQ (struct xgene_gpio_sb*,scalar_t__) ; 
 scalar_t__ HWIRQ_TO_GPIO (struct xgene_gpio_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 struct xgene_gpio_sb* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_create_fwspec_mapping (struct irq_fwspec*) ; 

__attribute__((used)) static int xgene_gpio_sb_to_irq(struct gpio_chip *gc, u32 gpio)
{
	struct xgene_gpio_sb *priv = gpiochip_get_data(gc);
	struct irq_fwspec fwspec;

	if ((gpio < priv->irq_start) ||
			(gpio > HWIRQ_TO_GPIO(priv, priv->nirq)))
		return -ENXIO;

	fwspec.fwnode = gc->parent->fwnode;
	fwspec.param_count = 2;
	fwspec.param[0] = GPIO_TO_HWIRQ(priv, gpio);
	fwspec.param[1] = IRQ_TYPE_NONE;
	return irq_create_fwspec_mapping(&fwspec);
}