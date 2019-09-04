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
struct mc13xxx {int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 

int mc13xxx_irq_mask(struct mc13xxx *mc13xxx, int irq)
{
	int virq = regmap_irq_get_virq(mc13xxx->irq_data, irq);

	disable_irq_nosync(virq);

	return 0;
}