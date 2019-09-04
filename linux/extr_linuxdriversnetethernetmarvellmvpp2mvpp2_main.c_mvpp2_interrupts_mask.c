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
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_ISR_RX_TX_MASK_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_percpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void mvpp2_interrupts_mask(void *arg)
{
	struct mvpp2_port *port = arg;

	mvpp2_percpu_write(port->priv, smp_processor_id(),
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), 0);
}