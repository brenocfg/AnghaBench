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
struct gpio_rcar_priv {int /*<<< orphan*/  lock; scalar_t__ has_outdtsel; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INOUTSEL ; 
 int /*<<< orphan*/  IOINTSEL ; 
 int /*<<< orphan*/  OUTDTSEL ; 
 int /*<<< orphan*/  POSNEG ; 
 int /*<<< orphan*/  gpio_rcar_modify_bit (struct gpio_rcar_priv*,int /*<<< orphan*/ ,unsigned int,int) ; 
 struct gpio_rcar_priv* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpio_rcar_config_general_input_output_mode(struct gpio_chip *chip,
						       unsigned int gpio,
						       bool output)
{
	struct gpio_rcar_priv *p = gpiochip_get_data(chip);
	unsigned long flags;

	/* follow steps in the GPIO documentation for
	 * "Setting General Output Mode" and
	 * "Setting General Input Mode"
	 */

	spin_lock_irqsave(&p->lock, flags);

	/* Configure postive logic in POSNEG */
	gpio_rcar_modify_bit(p, POSNEG, gpio, false);

	/* Select "General Input/Output Mode" in IOINTSEL */
	gpio_rcar_modify_bit(p, IOINTSEL, gpio, false);

	/* Select Input Mode or Output Mode in INOUTSEL */
	gpio_rcar_modify_bit(p, INOUTSEL, gpio, output);

	/* Select General Output Register to output data in OUTDTSEL */
	if (p->has_outdtsel && output)
		gpio_rcar_modify_bit(p, OUTDTSEL, gpio, false);

	spin_unlock_irqrestore(&p->lock, flags);
}