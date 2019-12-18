#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct mvpp2_port {int* rss_ctx; int /*<<< orphan*/  dev; TYPE_1__** rfs_rules; struct mvpp2* priv; } ;
struct mvpp2 {int /*<<< orphan*/ ** rss_tables; } ;
struct TYPE_4__ {int flow_type; int /*<<< orphan*/  location; } ;
struct ethtool_rxnfc {size_t rss_context; TYPE_2__ fs; } ;
struct TYPE_3__ {struct ethtool_rxnfc rxnfc; } ;

/* Variables and functions */
 int EINVAL ; 
 int FLOW_RSS ; 
 int MVPP22_N_RSS_TABLES ; 
 int MVPP2_N_RFS_ENTRIES_PER_FLOW ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int mvpp22_rss_ctx (struct mvpp2_port*,size_t) ; 
 int mvpp2_ethtool_cls_rule_del (struct mvpp2_port*,struct ethtool_rxnfc*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int mvpp22_port_rss_ctx_delete(struct mvpp2_port *port, u32 port_ctx)
{
	struct mvpp2 *priv = port->priv;
	struct ethtool_rxnfc *rxnfc;
	int i, rss_ctx, ret;

	rss_ctx = mvpp22_rss_ctx(port, port_ctx);

	if (rss_ctx < 0 || rss_ctx >= MVPP22_N_RSS_TABLES)
		return -EINVAL;

	/* Invalidate any active classification rule that use this context */
	for (i = 0; i < MVPP2_N_RFS_ENTRIES_PER_FLOW; i++) {
		if (!port->rfs_rules[i])
			continue;

		rxnfc = &port->rfs_rules[i]->rxnfc;
		if (!(rxnfc->fs.flow_type & FLOW_RSS) ||
		    rxnfc->rss_context != port_ctx)
			continue;

		ret = mvpp2_ethtool_cls_rule_del(port, rxnfc);
		if (ret) {
			netdev_warn(port->dev,
				    "couldn't remove classification rule %d associated to this context",
				    rxnfc->fs.location);
		}
	}

	kfree(priv->rss_tables[rss_ctx]);

	priv->rss_tables[rss_ctx] = NULL;
	port->rss_ctx[port_ctx] = -1;

	return 0;
}