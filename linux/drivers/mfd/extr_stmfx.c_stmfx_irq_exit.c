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
struct stmfx {int /*<<< orphan*/  irq_domain; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int STMFX_REG_IRQ_SRC_MAX ; 
 struct stmfx* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_find_mapping (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stmfx_irq_exit(struct i2c_client *client)
{
	struct stmfx *stmfx = i2c_get_clientdata(client);
	int hwirq;

	for (hwirq = 0; hwirq < STMFX_REG_IRQ_SRC_MAX; hwirq++)
		irq_dispose_mapping(irq_find_mapping(stmfx->irq_domain, hwirq));

	irq_domain_remove(stmfx->irq_domain);
}