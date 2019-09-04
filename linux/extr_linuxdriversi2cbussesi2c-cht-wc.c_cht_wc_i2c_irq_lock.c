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
struct cht_wc_i2c_adap {int /*<<< orphan*/  irqchip_lock; } ;

/* Variables and functions */
 struct cht_wc_i2c_adap* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cht_wc_i2c_irq_lock(struct irq_data *data)
{
	struct cht_wc_i2c_adap *adap = irq_data_get_irq_chip_data(data);

	mutex_lock(&adap->irqchip_lock);
}