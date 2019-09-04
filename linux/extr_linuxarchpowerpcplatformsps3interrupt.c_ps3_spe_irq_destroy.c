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

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  irq_get_irq_data (unsigned int) ; 
 int /*<<< orphan*/  ps3_chip_mask (int /*<<< orphan*/ ) ; 
 int ps3_irq_plug_destroy (unsigned int) ; 

int ps3_spe_irq_destroy(unsigned int virq)
{
	int result;

	ps3_chip_mask(irq_get_irq_data(virq));

	result = ps3_irq_plug_destroy(virq);
	BUG_ON(result);

	return result;
}