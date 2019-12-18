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
typedef  int /*<<< orphan*/  u32 ;
struct mvpp2_port {int nrxqs; int /*<<< orphan*/  priv; TYPE_1__** rxqs; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_RXQ_CONFIG_REG (int) ; 
 int /*<<< orphan*/  MVPP2_RXQ_DISABLE_MASK ; 
 int /*<<< orphan*/  mvpp2_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_ingress_disable(struct mvpp2_port *port)
{
	u32 val;
	int lrxq, queue;

	for (lrxq = 0; lrxq < port->nrxqs; lrxq++) {
		queue = port->rxqs[lrxq]->id;
		val = mvpp2_read(port->priv, MVPP2_RXQ_CONFIG_REG(queue));
		val |= MVPP2_RXQ_DISABLE_MASK;
		mvpp2_write(port->priv, MVPP2_RXQ_CONFIG_REG(queue), val);
	}
}