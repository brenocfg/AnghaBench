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
struct mvpp2_queue_vector {int /*<<< orphan*/  sw_thread_mask; struct mvpp2_port* port; } ;
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_ISR_DISABLE_INTERRUPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_ISR_ENABLE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mvpp2_qvec_interrupt_disable(struct mvpp2_queue_vector *qvec)
{
	struct mvpp2_port *port = qvec->port;

	mvpp2_write(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_DISABLE_INTERRUPT(qvec->sw_thread_mask));
}