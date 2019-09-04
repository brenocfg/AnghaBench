#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  domain; } ;
struct TYPE_4__ {TYPE_1__ irq; } ;
struct crystalcove_gpio {TYPE_2__ chip; int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int) ; 
 int CRYSTALCOVE_GPIO_NUM ; 
 int /*<<< orphan*/  GPIO0IRQ ; 
 int /*<<< orphan*/  GPIO1IRQ ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  handle_nested_irq (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,int) ; 
 scalar_t__ regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static irqreturn_t crystalcove_gpio_irq_handler(int irq, void *data)
{
	struct crystalcove_gpio *cg = data;
	unsigned int p0, p1;
	int pending;
	int gpio;
	unsigned int virq;

	if (regmap_read(cg->regmap, GPIO0IRQ, &p0) ||
	    regmap_read(cg->regmap, GPIO1IRQ, &p1))
		return IRQ_NONE;

	regmap_write(cg->regmap, GPIO0IRQ, p0);
	regmap_write(cg->regmap, GPIO1IRQ, p1);

	pending = p0 | p1 << 8;

	for (gpio = 0; gpio < CRYSTALCOVE_GPIO_NUM; gpio++) {
		if (pending & BIT(gpio)) {
			virq = irq_find_mapping(cg->chip.irq.domain, gpio);
			handle_nested_irq(virq);
		}
	}

	return IRQ_HANDLED;
}