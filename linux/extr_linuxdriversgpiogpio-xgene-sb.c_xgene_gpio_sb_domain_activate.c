#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct xgene_gpio_sb {scalar_t__ regs; TYPE_1__ gc; } ;
struct irq_domain {struct xgene_gpio_sb* host_data; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int HWIRQ_TO_GPIO (struct xgene_gpio_sb*,int /*<<< orphan*/ ) ; 
 scalar_t__ MPA_GPIO_SEL_LO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int gpiochip_lock_as_irq (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xgene_gpio_set_bit (TYPE_1__*,scalar_t__,int,int) ; 

__attribute__((used)) static int xgene_gpio_sb_domain_activate(struct irq_domain *d,
					 struct irq_data *irq_data,
					 bool reserve)
{
	struct xgene_gpio_sb *priv = d->host_data;
	u32 gpio = HWIRQ_TO_GPIO(priv, irq_data->hwirq);
	int ret;

	ret = gpiochip_lock_as_irq(&priv->gc, gpio);
	if (ret) {
		dev_err(priv->gc.parent,
		"Unable to configure XGene GPIO standby pin %d as IRQ\n",
				gpio);
		return ret;
	}

	xgene_gpio_set_bit(&priv->gc, priv->regs + MPA_GPIO_SEL_LO,
			gpio * 2, 1);
	return 0;
}