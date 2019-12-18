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
typedef  int /*<<< orphan*/  u32 ;
struct pic32_gpio_bank {scalar_t__ reg_base; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CNCON_REG ; 
 int /*<<< orphan*/  CNEN_REG ; 
 int /*<<< orphan*/  CNNE_REG ; 
 int EINVAL ; 
#define  IRQ_TYPE_EDGE_BOTH 130 
#define  IRQ_TYPE_EDGE_FALLING 129 
#define  IRQ_TYPE_EDGE_RISING 128 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 scalar_t__ PIC32_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_CNCON_EDGE ; 
 scalar_t__ PIC32_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 struct pic32_gpio_bank* irqd_to_bank (struct irq_data*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int pic32_gpio_irq_set_type(struct irq_data *data, unsigned int type)
{
	struct pic32_gpio_bank *bank = irqd_to_bank(data);
	u32 mask = BIT(data->hwirq);

	switch (type & IRQ_TYPE_SENSE_MASK) {
	case IRQ_TYPE_EDGE_RISING:
		/* enable RISE */
		writel(mask, bank->reg_base + PIC32_SET(CNEN_REG));
		/* disable FALL */
		writel(mask, bank->reg_base + PIC32_CLR(CNNE_REG));
		/* enable EDGE */
		writel(BIT(PIC32_CNCON_EDGE), bank->reg_base + PIC32_SET(CNCON_REG));
		break;
	case IRQ_TYPE_EDGE_FALLING:
		/* disable RISE */
		writel(mask, bank->reg_base + PIC32_CLR(CNEN_REG));
		/* enable FALL */
		writel(mask, bank->reg_base + PIC32_SET(CNNE_REG));
		/* enable EDGE */
		writel(BIT(PIC32_CNCON_EDGE), bank->reg_base + PIC32_SET(CNCON_REG));
		break;
	case IRQ_TYPE_EDGE_BOTH:
		/* enable RISE */
		writel(mask, bank->reg_base + PIC32_SET(CNEN_REG));
		/* enable FALL */
		writel(mask, bank->reg_base + PIC32_SET(CNNE_REG));
		/* enable EDGE */
		writel(BIT(PIC32_CNCON_EDGE), bank->reg_base + PIC32_SET(CNCON_REG));
		break;
	default:
		return -EINVAL;
	}

	irq_set_handler_locked(data, handle_edge_irq);

	return 0;
}