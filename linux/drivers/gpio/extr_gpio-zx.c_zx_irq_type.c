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
typedef  int /*<<< orphan*/  u16 ;
struct zx_gpio {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct irq_data {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 scalar_t__ ZX_GPIO_IEN ; 
 scalar_t__ ZX_GPIO_IEP ; 
 scalar_t__ ZX_GPIO_IV ; 
 scalar_t__ ZX_GPIO_IVE ; 
 int ZX_GPIO_NR ; 
 struct zx_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  readw_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writew_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int zx_irq_type(struct irq_data *d, unsigned trigger)
{
	struct gpio_chip *gc = irq_data_get_irq_chip_data(d);
	struct zx_gpio *chip = gpiochip_get_data(gc);
	int offset = irqd_to_hwirq(d);
	unsigned long flags;
	u16 gpiois, gpioi_epos, gpioi_eneg, gpioiev;
	u16 bit = BIT(offset);

	if (offset < 0 || offset >= ZX_GPIO_NR)
		return -EINVAL;

	raw_spin_lock_irqsave(&chip->lock, flags);

	gpioiev = readw_relaxed(chip->base + ZX_GPIO_IV);
	gpiois = readw_relaxed(chip->base + ZX_GPIO_IVE);
	gpioi_epos = readw_relaxed(chip->base + ZX_GPIO_IEP);
	gpioi_eneg = readw_relaxed(chip->base + ZX_GPIO_IEN);

	if (trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
		gpiois |= bit;
		if (trigger & IRQ_TYPE_LEVEL_HIGH)
			gpioiev |= bit;
		else
			gpioiev &= ~bit;
	} else
		gpiois &= ~bit;

	if ((trigger & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH) {
		gpioi_epos |= bit;
		gpioi_eneg |= bit;
	} else {
		if (trigger & IRQ_TYPE_EDGE_RISING) {
			gpioi_epos |= bit;
			gpioi_eneg &= ~bit;
		} else if (trigger & IRQ_TYPE_EDGE_FALLING) {
			gpioi_eneg |= bit;
			gpioi_epos &= ~bit;
		}
	}

	writew_relaxed(gpiois, chip->base + ZX_GPIO_IVE);
	writew_relaxed(gpioi_epos, chip->base + ZX_GPIO_IEP);
	writew_relaxed(gpioi_eneg, chip->base + ZX_GPIO_IEN);
	writew_relaxed(gpioiev, chip->base + ZX_GPIO_IV);
	raw_spin_unlock_irqrestore(&chip->lock, flags);

	return 0;
}