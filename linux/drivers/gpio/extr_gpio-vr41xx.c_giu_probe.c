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
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct irq_chip {int dummy; } ;
struct TYPE_3__ {int ngpio; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GIUINTENH ; 
 int /*<<< orphan*/  GIUINTENL ; 
 int /*<<< orphan*/  GIUINTTYPH ; 
 int /*<<< orphan*/  GIUINTTYPL ; 
 unsigned int GIUINT_HIGH_OFFSET ; 
 unsigned int GIU_IRQ_BASE ; 
 unsigned int GIU_IRQ_LAST ; 
#define  GPIO_36PINS 130 
#define  GPIO_48PINS_EDGE_SELECT 129 
#define  GPIO_50PINS_PULLUPDOWN 128 
 int /*<<< orphan*/  GPIO_HAS_INTERRUPT_EDGE_SELECT ; 
 int /*<<< orphan*/  GPIO_HAS_PULLUPDOWN_IO ; 
 unsigned int GPIO_PIN_OF_IRQ (unsigned int) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cascade_irq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  giu_base ; 
 int /*<<< orphan*/  giu_flags ; 
 int /*<<< orphan*/  giu_get_irq ; 
 unsigned int giu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  giu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct irq_chip giuint_high_irq_chip ; 
 struct irq_chip giuint_low_irq_chip ; 
 scalar_t__ gpiochip_add_data (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  irq_set_chip_and_handler (unsigned int,struct irq_chip*,int /*<<< orphan*/ ) ; 
 int nr_irqs ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__ vr41xx_gpio_chip ; 

__attribute__((used)) static int giu_probe(struct platform_device *pdev)
{
	unsigned int trigger, i, pin;
	struct irq_chip *chip;
	int irq;

	switch (pdev->id) {
	case GPIO_50PINS_PULLUPDOWN:
		giu_flags = GPIO_HAS_PULLUPDOWN_IO;
		vr41xx_gpio_chip.ngpio = 50;
		break;
	case GPIO_36PINS:
		vr41xx_gpio_chip.ngpio = 36;
		break;
	case GPIO_48PINS_EDGE_SELECT:
		giu_flags = GPIO_HAS_INTERRUPT_EDGE_SELECT;
		vr41xx_gpio_chip.ngpio = 48;
		break;
	default:
		dev_err(&pdev->dev, "GIU: unknown ID %d\n", pdev->id);
		return -ENODEV;
	}

	giu_base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(giu_base))
		return PTR_ERR(giu_base);

	vr41xx_gpio_chip.parent = &pdev->dev;

	if (gpiochip_add_data(&vr41xx_gpio_chip, NULL))
		return -ENODEV;

	giu_write(GIUINTENL, 0);
	giu_write(GIUINTENH, 0);

	trigger = giu_read(GIUINTTYPH) << 16;
	trigger |= giu_read(GIUINTTYPL);
	for (i = GIU_IRQ_BASE; i <= GIU_IRQ_LAST; i++) {
		pin = GPIO_PIN_OF_IRQ(i);
		if (pin < GIUINT_HIGH_OFFSET)
			chip = &giuint_low_irq_chip;
		else
			chip = &giuint_high_irq_chip;

		if (trigger & (1 << pin))
			irq_set_chip_and_handler(i, chip, handle_edge_irq);
		else
			irq_set_chip_and_handler(i, chip, handle_level_irq);

	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0 || irq >= nr_irqs)
		return -EBUSY;

	return cascade_irq(irq, giu_get_irq);
}