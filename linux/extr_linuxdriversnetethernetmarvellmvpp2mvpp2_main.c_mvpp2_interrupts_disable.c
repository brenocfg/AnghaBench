#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int nqvecs; int /*<<< orphan*/  id; int /*<<< orphan*/  priv; TYPE_1__* qvecs; } ;
struct TYPE_2__ {int sw_thread_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_ISR_DISABLE_INTERRUPT (int) ; 
 int /*<<< orphan*/  MVPP2_ISR_ENABLE_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mvpp2_interrupts_disable(struct mvpp2_port *port)
{
	int i, sw_thread_mask = 0;

	for (i = 0; i < port->nqvecs; i++)
		sw_thread_mask |= port->qvecs[i].sw_thread_mask;

	mvpp2_write(port->priv, MVPP2_ISR_ENABLE_REG(port->id),
		    MVPP2_ISR_DISABLE_INTERRUPT(sw_thread_mask));
}