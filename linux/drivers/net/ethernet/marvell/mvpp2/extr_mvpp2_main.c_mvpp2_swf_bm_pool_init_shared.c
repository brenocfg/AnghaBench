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
struct mvpp2_port {scalar_t__ pkt_size; int nrxqs; TYPE_2__* pool_short; int /*<<< orphan*/  id; TYPE_1__* pool_long; } ;
typedef  enum mvpp2_bm_pool_log_num { ____Placeholder_mvpp2_bm_pool_log_num } mvpp2_bm_pool_log_num ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  port_map; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  port_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int MVPP2_BM_JUMBO ; 
 int MVPP2_BM_LONG ; 
 scalar_t__ MVPP2_BM_LONG_PKT_SIZE ; 
 int MVPP2_BM_SHORT ; 
 void* mvpp2_bm_pool_use (struct mvpp2_port*,int,int /*<<< orphan*/ ) ; 
 TYPE_3__* mvpp2_pools ; 
 int /*<<< orphan*/  mvpp2_rxq_long_pool_set (struct mvpp2_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_rxq_short_pool_set (struct mvpp2_port*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_swf_bm_pool_init_shared(struct mvpp2_port *port)
{
	enum mvpp2_bm_pool_log_num long_log_pool, short_log_pool;
	int rxq;

	/* If port pkt_size is higher than 1518B:
	 * HW Long pool - SW Jumbo pool, HW Short pool - SW Long pool
	 * else: HW Long pool - SW Long pool, HW Short pool - SW Short pool
	 */
	if (port->pkt_size > MVPP2_BM_LONG_PKT_SIZE) {
		long_log_pool = MVPP2_BM_JUMBO;
		short_log_pool = MVPP2_BM_LONG;
	} else {
		long_log_pool = MVPP2_BM_LONG;
		short_log_pool = MVPP2_BM_SHORT;
	}

	if (!port->pool_long) {
		port->pool_long =
			mvpp2_bm_pool_use(port, long_log_pool,
					  mvpp2_pools[long_log_pool].pkt_size);
		if (!port->pool_long)
			return -ENOMEM;

		port->pool_long->port_map |= BIT(port->id);

		for (rxq = 0; rxq < port->nrxqs; rxq++)
			mvpp2_rxq_long_pool_set(port, rxq, port->pool_long->id);
	}

	if (!port->pool_short) {
		port->pool_short =
			mvpp2_bm_pool_use(port, short_log_pool,
					  mvpp2_pools[short_log_pool].pkt_size);
		if (!port->pool_short)
			return -ENOMEM;

		port->pool_short->port_map |= BIT(port->id);

		for (rxq = 0; rxq < port->nrxqs; rxq++)
			mvpp2_rxq_short_pool_set(port, rxq,
						 port->pool_short->id);
	}

	return 0;
}