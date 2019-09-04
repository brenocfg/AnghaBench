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
struct gpio_rcar_priv {int /*<<< orphan*/  lock; scalar_t__ has_both_edge_trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  BOTHEDGE ; 
 int /*<<< orphan*/  EDGLEVEL ; 
 int /*<<< orphan*/  INTCLR ; 
 int /*<<< orphan*/  IOINTSEL ; 
 int /*<<< orphan*/  POSNEG ; 
 int /*<<< orphan*/  gpio_rcar_modify_bit (struct gpio_rcar_priv*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gpio_rcar_write (struct gpio_rcar_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpio_rcar_config_interrupt_input_mode(struct gpio_rcar_priv *p,
						  unsigned int hwirq,
						  bool active_high_rising_edge,
						  bool level_trigger,
						  bool both)
{
	unsigned long flags;

	/* follow steps in the GPIO documentation for
	 * "Setting Edge-Sensitive Interrupt Input Mode" and
	 * "Setting Level-Sensitive Interrupt Input Mode"
	 */

	spin_lock_irqsave(&p->lock, flags);

	/* Configure postive or negative logic in POSNEG */
	gpio_rcar_modify_bit(p, POSNEG, hwirq, !active_high_rising_edge);

	/* Configure edge or level trigger in EDGLEVEL */
	gpio_rcar_modify_bit(p, EDGLEVEL, hwirq, !level_trigger);

	/* Select one edge or both edges in BOTHEDGE */
	if (p->has_both_edge_trigger)
		gpio_rcar_modify_bit(p, BOTHEDGE, hwirq, both);

	/* Select "Interrupt Input Mode" in IOINTSEL */
	gpio_rcar_modify_bit(p, IOINTSEL, hwirq, true);

	/* Write INTCLR in case of edge trigger */
	if (!level_trigger)
		gpio_rcar_write(p, INTCLR, BIT(hwirq));

	spin_unlock_irqrestore(&p->lock, flags);
}