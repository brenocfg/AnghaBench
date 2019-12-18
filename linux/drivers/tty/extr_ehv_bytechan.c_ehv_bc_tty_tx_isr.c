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
struct ehv_bc_data {int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ehv_bc_tx_dequeue (struct ehv_bc_data*) ; 
 int /*<<< orphan*/  tty_port_tty_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ehv_bc_tty_tx_isr(int irq, void *data)
{
	struct ehv_bc_data *bc = data;

	ehv_bc_tx_dequeue(bc);
	tty_port_tty_wakeup(&bc->port);

	return IRQ_HANDLED;
}