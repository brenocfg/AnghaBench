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
typedef  unsigned int u32 ;
struct u300_gpio {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int U300_GPIO_PXPCR_PIN_MODE_MASK ; 
 int /*<<< orphan*/  U300_PIN_REG (unsigned int,int /*<<< orphan*/ ) ; 
 struct u300_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pcr ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u300_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct u300_gpio *gpio = gpiochip_get_data(chip);
	unsigned long flags;
	u32 val;

	local_irq_save(flags);
	val = readl(U300_PIN_REG(offset, pcr));
	/* Mask out this pin, note 2 bits per setting */
	val &= ~(U300_GPIO_PXPCR_PIN_MODE_MASK << ((offset & 0x07) << 1));
	writel(val, U300_PIN_REG(offset, pcr));
	local_irq_restore(flags);
	return 0;
}