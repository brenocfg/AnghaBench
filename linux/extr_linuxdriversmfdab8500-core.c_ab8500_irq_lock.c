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
struct irq_data {int dummy; } ;
struct ab8500 {int /*<<< orphan*/  transfer_ongoing; int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct ab8500* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ab8500_irq_lock(struct irq_data *data)
{
	struct ab8500 *ab8500 = irq_data_get_irq_chip_data(data);

	mutex_lock(&ab8500->irq_lock);
	atomic_inc(&ab8500->transfer_ongoing);
}