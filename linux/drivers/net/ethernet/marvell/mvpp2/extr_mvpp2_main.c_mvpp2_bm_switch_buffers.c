#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mvpp2_port {int nrxqs; TYPE_2__* dev; } ;
struct mvpp2 {int port_count; int percpu_pools; struct mvpp2_port** port_list; int /*<<< orphan*/ * bm_pools; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int MVPP2_BM_POOLS_NUM ; 
 int MVPP2_MAX_PORTS ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_bm_init (int /*<<< orphan*/ ,struct mvpp2*) ; 
 int /*<<< orphan*/  mvpp2_bm_pool_destroy (int /*<<< orphan*/ ,struct mvpp2*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_open (TYPE_2__*) ; 
 int /*<<< orphan*/  mvpp2_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  mvpp2_swf_bm_pool_init (struct mvpp2_port*) ; 
 int netif_running (TYPE_2__*) ; 

__attribute__((used)) static int mvpp2_bm_switch_buffers(struct mvpp2 *priv, bool percpu)
{
	int numbufs = MVPP2_BM_POOLS_NUM, i;
	struct mvpp2_port *port = NULL;
	bool status[MVPP2_MAX_PORTS];

	for (i = 0; i < priv->port_count; i++) {
		port = priv->port_list[i];
		status[i] = netif_running(port->dev);
		if (status[i])
			mvpp2_stop(port->dev);
	}

	/* nrxqs is the same for all ports */
	if (priv->percpu_pools)
		numbufs = port->nrxqs * 2;

	for (i = 0; i < numbufs; i++)
		mvpp2_bm_pool_destroy(port->dev->dev.parent, priv, &priv->bm_pools[i]);

	devm_kfree(port->dev->dev.parent, priv->bm_pools);
	priv->percpu_pools = percpu;
	mvpp2_bm_init(port->dev->dev.parent, priv);

	for (i = 0; i < priv->port_count; i++) {
		port = priv->port_list[i];
		mvpp2_swf_bm_pool_init(port);
		if (status[i])
			mvpp2_open(port->dev);
	}

	return 0;
}