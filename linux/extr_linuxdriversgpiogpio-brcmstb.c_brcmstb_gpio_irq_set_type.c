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
typedef  int u32 ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct gpio_chip {int dummy; } ;
struct brcmstb_gpio_priv {scalar_t__ reg_base; } ;
struct TYPE_2__ {int (* read_reg ) (scalar_t__) ;int /*<<< orphan*/  bgpio_lock; int /*<<< orphan*/  (* write_reg ) (scalar_t__,int) ;} ;
struct brcmstb_gpio_bank {TYPE_1__ gc; int /*<<< orphan*/  id; struct brcmstb_gpio_priv* parent_priv; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ GIO_EC (int /*<<< orphan*/ ) ; 
 scalar_t__ GIO_EI (int /*<<< orphan*/ ) ; 
 scalar_t__ GIO_LEVEL (int /*<<< orphan*/ ) ; 
#define  IRQ_TYPE_EDGE_BOTH 132 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 int /*<<< orphan*/  brcmstb_gpio_hwirq_to_offset (int /*<<< orphan*/ ,struct brcmstb_gpio_bank*) ; 
 struct brcmstb_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (scalar_t__) ; 
 int stub2 (scalar_t__) ; 
 int stub3 (scalar_t__) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int) ; 

__attribute__((used)) static int brcmstb_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct brcmstb_gpio_bank *bank = gpiochip_get_data(gc);
	struct brcmstb_gpio_priv *priv = bank->parent_priv;
	u32 mask = BIT(brcmstb_gpio_hwirq_to_offset(d->hwirq, bank));
	u32 edge_insensitive, iedge_insensitive;
	u32 edge_config, iedge_config;
	u32 level, ilevel;
	unsigned long flags;

	switch (type) {
	case IRQ_TYPE_LEVEL_LOW:
		level = mask;
		edge_config = 0;
		edge_insensitive = 0;
		break;
	case IRQ_TYPE_LEVEL_HIGH:
		level = mask;
		edge_config = mask;
		edge_insensitive = 0;
		break;
	case IRQ_TYPE_EDGE_FALLING:
		level = 0;
		edge_config = 0;
		edge_insensitive = 0;
		break;
	case IRQ_TYPE_EDGE_RISING:
		level = 0;
		edge_config = mask;
		edge_insensitive = 0;
		break;
	case IRQ_TYPE_EDGE_BOTH:
		level = 0;
		edge_config = 0;  /* don't care, but want known value */
		edge_insensitive = mask;
		break;
	default:
		return -EINVAL;
	}

	spin_lock_irqsave(&bank->gc.bgpio_lock, flags);

	iedge_config = bank->gc.read_reg(priv->reg_base +
			GIO_EC(bank->id)) & ~mask;
	iedge_insensitive = bank->gc.read_reg(priv->reg_base +
			GIO_EI(bank->id)) & ~mask;
	ilevel = bank->gc.read_reg(priv->reg_base +
			GIO_LEVEL(bank->id)) & ~mask;

	bank->gc.write_reg(priv->reg_base + GIO_EC(bank->id),
			iedge_config | edge_config);
	bank->gc.write_reg(priv->reg_base + GIO_EI(bank->id),
			iedge_insensitive | edge_insensitive);
	bank->gc.write_reg(priv->reg_base + GIO_LEVEL(bank->id),
			ilevel | level);

	spin_unlock_irqrestore(&bank->gc.bgpio_lock, flags);
	return 0;
}