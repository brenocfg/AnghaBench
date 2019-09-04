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
typedef  scalar_t__ u8 ;
struct stmpe_variant_info {int /*<<< orphan*/  num_irqs; } ;
struct stmpe {scalar_t__* ier; scalar_t__* oldier; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/ * regs; struct stmpe_variant_info* variant; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int STMPE_IDX_IER_LSB ; 
 struct stmpe* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stmpe_reg_write (struct stmpe*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stmpe_irq_sync_unlock(struct irq_data *data)
{
	struct stmpe *stmpe = irq_data_get_irq_chip_data(data);
	struct stmpe_variant_info *variant = stmpe->variant;
	int num = DIV_ROUND_UP(variant->num_irqs, 8);
	int i;

	for (i = 0; i < num; i++) {
		u8 new = stmpe->ier[i];
		u8 old = stmpe->oldier[i];

		if (new == old)
			continue;

		stmpe->oldier[i] = new;
		stmpe_reg_write(stmpe, stmpe->regs[STMPE_IDX_IER_LSB + i], new);
	}

	mutex_unlock(&stmpe->irq_lock);
}