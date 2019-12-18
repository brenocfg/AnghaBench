#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int nrxqs; int /*<<< orphan*/ * pool_short; int /*<<< orphan*/ * pool_long; TYPE_2__* priv; int /*<<< orphan*/  id; } ;
struct mvpp2_bm_pool {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_size; } ;
struct TYPE_5__ {TYPE_1__* bm_pools; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  port_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 size_t MVPP2_BM_LONG ; 
 size_t MVPP2_BM_SHORT ; 
 struct mvpp2_bm_pool* mvpp2_bm_pool_use_percpu (struct mvpp2_port*,size_t,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* mvpp2_pools ; 
 int /*<<< orphan*/  mvpp2_rxq_long_pool_set (struct mvpp2_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_rxq_short_pool_set (struct mvpp2_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_swf_bm_pool_init_percpu(struct mvpp2_port *port)
{
	struct mvpp2_bm_pool *p;
	int i;

	for (i = 0; i < port->nrxqs; i++) {
		p = mvpp2_bm_pool_use_percpu(port, MVPP2_BM_SHORT, i,
					     mvpp2_pools[MVPP2_BM_SHORT].pkt_size);
		if (!p)
			return -ENOMEM;

		port->priv->bm_pools[i].port_map |= BIT(port->id);
		mvpp2_rxq_short_pool_set(port, i, port->priv->bm_pools[i].id);
	}

	for (i = 0; i < port->nrxqs; i++) {
		p = mvpp2_bm_pool_use_percpu(port, MVPP2_BM_LONG, i + port->nrxqs,
					     mvpp2_pools[MVPP2_BM_LONG].pkt_size);
		if (!p)
			return -ENOMEM;

		port->priv->bm_pools[i + port->nrxqs].port_map |= BIT(port->id);
		mvpp2_rxq_long_pool_set(port, i,
					port->priv->bm_pools[i + port->nrxqs].id);
	}

	port->pool_long = NULL;
	port->pool_short = NULL;

	return 0;
}