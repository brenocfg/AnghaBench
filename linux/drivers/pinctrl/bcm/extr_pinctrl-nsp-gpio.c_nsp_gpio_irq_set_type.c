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
struct nsp_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_FALLING 131 
#define  IRQ_TYPE_EDGE_RISING 130 
#define  IRQ_TYPE_LEVEL_HIGH 129 
#define  IRQ_TYPE_LEVEL_LOW 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  NSP_GPIO_EVENT_INT_POLARITY ; 
 int /*<<< orphan*/  NSP_GPIO_INT_POLARITY ; 
 int /*<<< orphan*/  REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,char*,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 struct nsp_gpio* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int nsp_get_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nsp_set_bit (struct nsp_gpio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp_gpio_irq_set_type(struct irq_data *d, unsigned int type)
{
	struct nsp_gpio *chip = irq_data_get_irq_chip_data(d);
	unsigned gpio = d->hwirq;
	bool level_low;
	bool falling;
	unsigned long flags;

	raw_spin_lock_irqsave(&chip->lock, flags);
	falling = nsp_get_bit(chip, REG, NSP_GPIO_EVENT_INT_POLARITY, gpio);
	level_low = nsp_get_bit(chip, REG, NSP_GPIO_INT_POLARITY, gpio);

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		falling = false;
		break;

	case IRQ_TYPE_EDGE_FALLING:
		falling = true;
		break;

	case IRQ_TYPE_LEVEL_HIGH:
		level_low = false;
		break;

	case IRQ_TYPE_LEVEL_LOW:
		level_low = true;
		break;

	default:
		dev_err(chip->dev, "invalid GPIO IRQ type 0x%x\n",
			type);
		raw_spin_unlock_irqrestore(&chip->lock, flags);
		return -EINVAL;
	}

	nsp_set_bit(chip, REG, NSP_GPIO_EVENT_INT_POLARITY, gpio, falling);
	nsp_set_bit(chip, REG, NSP_GPIO_INT_POLARITY, gpio, level_low);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	dev_dbg(chip->dev, "gpio:%u level_low:%s falling:%s\n", gpio,
		level_low ? "true" : "false", falling ? "true" : "false");
	return 0;
}