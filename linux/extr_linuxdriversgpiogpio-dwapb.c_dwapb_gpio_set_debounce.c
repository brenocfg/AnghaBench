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
struct gpio_chip {int /*<<< orphan*/  bgpio_lock; } ;
struct dwapb_gpio_port {struct dwapb_gpio* gpio; } ;
struct dwapb_gpio {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 int /*<<< orphan*/  GPIO_PORTA_DEBOUNCE ; 
 unsigned long dwapb_read (struct dwapb_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwapb_write (struct dwapb_gpio*,int /*<<< orphan*/ ,unsigned long) ; 
 struct dwapb_gpio_port* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwapb_gpio_set_debounce(struct gpio_chip *gc,
				   unsigned offset, unsigned debounce)
{
	struct dwapb_gpio_port *port = gpiochip_get_data(gc);
	struct dwapb_gpio *gpio = port->gpio;
	unsigned long flags, val_deb;
	unsigned long mask = BIT(offset);

	spin_lock_irqsave(&gc->bgpio_lock, flags);

	val_deb = dwapb_read(gpio, GPIO_PORTA_DEBOUNCE);
	if (debounce)
		dwapb_write(gpio, GPIO_PORTA_DEBOUNCE, val_deb | mask);
	else
		dwapb_write(gpio, GPIO_PORTA_DEBOUNCE, val_deb & ~mask);

	spin_unlock_irqrestore(&gc->bgpio_lock, flags);

	return 0;
}