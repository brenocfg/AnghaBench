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
struct nmk_gpio_chip {int /*<<< orphan*/  bank; int /*<<< orphan*/  (* get_latent_status ) (int /*<<< orphan*/ ) ;} ;
struct irq_desc {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nmk_gpio_irq_handler (struct irq_desc*,int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_desc_get_handler_data (struct irq_desc*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nmk_gpio_latent_irq_handler(struct irq_desc *desc)
{
	struct gpio_chip *chip = irq_desc_get_handler_data(desc);
	struct nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	u32 status = nmk_chip->get_latent_status(nmk_chip->bank);

	__nmk_gpio_irq_handler(desc, status);
}