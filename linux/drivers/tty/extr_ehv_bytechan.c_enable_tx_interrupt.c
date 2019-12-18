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
struct ehv_bc_data {int tx_irq_enabled; int /*<<< orphan*/  tx_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_tx_interrupt(struct ehv_bc_data *bc)
{
	if (!bc->tx_irq_enabled) {
		enable_irq(bc->tx_irq);
		bc->tx_irq_enabled = 1;
	}
}