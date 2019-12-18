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
struct rcar_msi {int dummy; } ;
struct msi_controller {int dummy; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 struct irq_data* irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  rcar_msi_free (struct rcar_msi*,int /*<<< orphan*/ ) ; 
 struct rcar_msi* to_rcar_msi (struct msi_controller*) ; 

__attribute__((used)) static void rcar_msi_teardown_irq(struct msi_controller *chip, unsigned int irq)
{
	struct rcar_msi *msi = to_rcar_msi(chip);
	struct irq_data *d = irq_get_irq_data(irq);

	rcar_msi_free(msi, d->hwirq);
}