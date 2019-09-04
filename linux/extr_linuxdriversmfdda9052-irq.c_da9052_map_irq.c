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
struct da9052 {int /*<<< orphan*/  irq_data; } ;

/* Variables and functions */
 int regmap_irq_get_virq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int da9052_map_irq(struct da9052 *da9052, int irq)
{
	return regmap_irq_get_virq(da9052->irq_data, irq);
}