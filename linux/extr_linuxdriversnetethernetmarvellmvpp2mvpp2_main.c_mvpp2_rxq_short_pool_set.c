#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mvpp2_port {TYPE_2__* priv; TYPE_1__** rxqs; } ;
struct TYPE_5__ {scalar_t__ hw_version; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 scalar_t__ MVPP21 ; 
 int MVPP21_RXQ_POOL_SHORT_MASK ; 
 int MVPP22_RXQ_POOL_SHORT_MASK ; 
 int /*<<< orphan*/  MVPP2_RXQ_CONFIG_REG (int) ; 
 int MVPP2_RXQ_POOL_SHORT_OFFS ; 
 int mvpp2_read (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp2_rxq_short_pool_set(struct mvpp2_port *port,
				     int lrxq, int short_pool)
{
	u32 val, mask;
	int prxq;

	/* Get queue physical ID */
	prxq = port->rxqs[lrxq]->id;

	if (port->priv->hw_version == MVPP21)
		mask = MVPP21_RXQ_POOL_SHORT_MASK;
	else
		mask = MVPP22_RXQ_POOL_SHORT_MASK;

	val = mvpp2_read(port->priv, MVPP2_RXQ_CONFIG_REG(prxq));
	val &= ~mask;
	val |= (short_pool << MVPP2_RXQ_POOL_SHORT_OFFS) & mask;
	mvpp2_write(port->priv, MVPP2_RXQ_CONFIG_REG(prxq), val);
}