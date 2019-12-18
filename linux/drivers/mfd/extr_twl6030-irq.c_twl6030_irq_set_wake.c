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
struct twl6030_irq {int /*<<< orphan*/  wakeirqs; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct twl6030_irq* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static int twl6030_irq_set_wake(struct irq_data *d, unsigned int on)
{
	struct twl6030_irq *pdata = irq_data_get_irq_chip_data(d);

	if (on)
		atomic_inc(&pdata->wakeirqs);
	else
		atomic_dec(&pdata->wakeirqs);

	return 0;
}