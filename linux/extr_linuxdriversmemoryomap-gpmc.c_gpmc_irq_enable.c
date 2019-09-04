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

/* Variables and functions */
 int /*<<< orphan*/  gpmc_irq_endis (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpmc_irq_enable(struct irq_data *p)
{
	gpmc_irq_endis(p->hwirq, true);
}