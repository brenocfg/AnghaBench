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
struct npcm7xx_gpio {scalar_t__ base; } ;
struct irq_data {unsigned int hwirq; int /*<<< orphan*/  irq; TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ NPCM7XX_GP_N_EVST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct npcm7xx_gpio* gpiochip_get_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void npcmgpio_irq_ack(struct irq_data *d)
{
	struct npcm7xx_gpio *bank =
		gpiochip_get_data(irq_data_get_irq_chip_data(d));
	unsigned int gpio = d->hwirq;

	dev_dbg(d->chip->parent_device, "irq_ack: %u.%u\n", gpio, d->irq);
	iowrite32(BIT(gpio), bank->base + NPCM7XX_GP_N_EVST);
}