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
struct da9052 {int dummy; } ;

/* Variables and functions */
 int da9052_map_irq (struct da9052*,int) ; 
 int /*<<< orphan*/  enable_irq (int) ; 

int da9052_enable_irq(struct da9052 *da9052, int irq)
{
	irq = da9052_map_irq(da9052, irq);
	if (irq < 0)
		return irq;

	enable_irq(irq);

	return 0;
}