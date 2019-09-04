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
struct mvpp2_port {int ntxqs; int /*<<< orphan*/  priv; TYPE_1__** txqs; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_TXQ_SENT_REG (int) ; 
 int /*<<< orphan*/  mvpp2_percpu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void mvpp2_txq_sent_counter_clear(void *arg)
{
	struct mvpp2_port *port = arg;
	int queue;

	for (queue = 0; queue < port->ntxqs; queue++) {
		int id = port->txqs[queue]->id;

		mvpp2_percpu_read(port->priv, smp_processor_id(),
				  MVPP2_TXQ_SENT_REG(id));
	}
}