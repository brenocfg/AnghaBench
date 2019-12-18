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
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct irq_chip_generic {struct al_fic* private; } ;
struct al_fic {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AL_FIC_SET_CAUSE ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 struct irq_chip_generic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int al_fic_irq_retrigger(struct irq_data *data)
{
	struct irq_chip_generic *gc = irq_data_get_irq_chip_data(data);
	struct al_fic *fic = gc->private;

	writel_relaxed(BIT(data->hwirq), fic->base + AL_FIC_SET_CAUSE);

	return 1;
}