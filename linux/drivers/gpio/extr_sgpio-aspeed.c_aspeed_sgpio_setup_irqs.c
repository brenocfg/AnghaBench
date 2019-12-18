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
struct platform_device {int dummy; } ;
struct gpio_irq_chip {int* parents; int num_parents; struct aspeed_sgpio* parent_handler_data; int /*<<< orphan*/  parent_handler; int /*<<< orphan*/  default_type; int /*<<< orphan*/  handler; int /*<<< orphan*/ * chip; } ;
struct aspeed_sgpio_bank {int dummy; } ;
struct TYPE_2__ {struct gpio_irq_chip irq; } ;
struct aspeed_sgpio {int irq; TYPE_1__ chip; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct aspeed_sgpio_bank*) ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 struct aspeed_sgpio_bank* aspeed_sgpio_banks ; 
 int /*<<< orphan*/  aspeed_sgpio_irq_handler ; 
 int /*<<< orphan*/  aspeed_sgpio_irqchip ; 
 int /*<<< orphan*/  bank_reg (struct aspeed_sgpio*,struct aspeed_sgpio_bank const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_bad_irq ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_irq_enable ; 
 int /*<<< orphan*/  reg_irq_status ; 
 int /*<<< orphan*/  reg_irq_type0 ; 
 int /*<<< orphan*/  reg_irq_type1 ; 
 int /*<<< orphan*/  reg_irq_type2 ; 

__attribute__((used)) static int aspeed_sgpio_setup_irqs(struct aspeed_sgpio *gpio,
				   struct platform_device *pdev)
{
	int rc, i;
	const struct aspeed_sgpio_bank *bank;
	struct gpio_irq_chip *irq;

	rc = platform_get_irq(pdev, 0);
	if (rc < 0)
		return rc;

	gpio->irq = rc;

	/* Disable IRQ and clear Interrupt status registers for all SPGIO Pins. */
	for (i = 0; i < ARRAY_SIZE(aspeed_sgpio_banks); i++) {
		bank =  &aspeed_sgpio_banks[i];
		/* disable irq enable bits */
		iowrite32(0x00000000, bank_reg(gpio, bank, reg_irq_enable));
		/* clear status bits */
		iowrite32(0xffffffff, bank_reg(gpio, bank, reg_irq_status));
	}

	irq = &gpio->chip.irq;
	irq->chip = &aspeed_sgpio_irqchip;
	irq->handler = handle_bad_irq;
	irq->default_type = IRQ_TYPE_NONE;
	irq->parent_handler = aspeed_sgpio_irq_handler;
	irq->parent_handler_data = gpio;
	irq->parents = &gpio->irq;
	irq->num_parents = 1;

	/* set IRQ settings and Enable Interrupt */
	for (i = 0; i < ARRAY_SIZE(aspeed_sgpio_banks); i++) {
		bank = &aspeed_sgpio_banks[i];
		/* set falling or level-low irq */
		iowrite32(0x00000000, bank_reg(gpio, bank, reg_irq_type0));
		/* trigger type is edge */
		iowrite32(0x00000000, bank_reg(gpio, bank, reg_irq_type1));
		/* dual edge trigger mode. */
		iowrite32(0xffffffff, bank_reg(gpio, bank, reg_irq_type2));
		/* enable irq */
		iowrite32(0xffffffff, bank_reg(gpio, bank, reg_irq_enable));
	}

	return 0;
}