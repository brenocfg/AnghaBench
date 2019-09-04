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
struct tps65217 {int /*<<< orphan*/  irq_lock; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 struct tps65217* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tps65217_irq_lock(struct irq_data *data)
{
	struct tps65217 *tps = irq_data_get_irq_chip_data(data);

	mutex_lock(&tps->irq_lock);
}