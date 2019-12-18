#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int /*<<< orphan*/  id; TYPE_1__* priv; } ;
struct TYPE_3__ {scalar_t__ nthreads; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_ISR_RX_TX_MASK_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cpu_to_thread (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_thread_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void mvpp2_interrupts_mask(void *arg)
{
	struct mvpp2_port *port = arg;

	/* If the thread isn't used, don't do anything */
	if (smp_processor_id() > port->priv->nthreads)
		return;

	mvpp2_thread_write(port->priv,
			   mvpp2_cpu_to_thread(port->priv, smp_processor_id()),
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), 0);
}