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
struct stmfx {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_src; int /*<<< orphan*/  map; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STMFX_REG_IRQ_SRC_EN ; 
 struct stmfx* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmfx_irq_bus_sync_unlock(struct irq_data *data)
{
	struct stmfx *stmfx = irq_data_get_irq_chip_data(data);

	regmap_write(stmfx->map, STMFX_REG_IRQ_SRC_EN, stmfx->irq_src);

	mutex_unlock(&stmfx->lock);
}