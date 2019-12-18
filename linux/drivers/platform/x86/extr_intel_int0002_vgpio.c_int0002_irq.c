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
struct TYPE_2__ {int /*<<< orphan*/  domain; } ;
struct gpio_chip {int /*<<< orphan*/  parent; TYPE_1__ irq; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int GPE0A_PME_B0_STS_BIT ; 
 int /*<<< orphan*/  GPE0A_PME_B0_VIRT_GPIO_PIN ; 
 int /*<<< orphan*/  GPE0A_STS_PORT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_hard_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t int0002_irq(int irq, void *data)
{
	struct gpio_chip *chip = data;
	u32 gpe_sts_reg;

	gpe_sts_reg = inl(GPE0A_STS_PORT);
	if (!(gpe_sts_reg & GPE0A_PME_B0_STS_BIT))
		return IRQ_NONE;

	generic_handle_irq(irq_find_mapping(chip->irq.domain,
					    GPE0A_PME_B0_VIRT_GPIO_PIN));

	pm_wakeup_hard_event(chip->parent);

	return IRQ_HANDLED;
}