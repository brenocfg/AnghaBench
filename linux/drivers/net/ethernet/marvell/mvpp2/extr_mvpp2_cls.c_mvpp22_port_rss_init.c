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
typedef  int u32 ;
struct mvpp2_rss_table {int /*<<< orphan*/ * indir; } ;
struct mvpp2_port {int* rss_ctx; int /*<<< orphan*/  nrxqs; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP4_2T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP4_5T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP6_2T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP6_5T ; 
 int /*<<< orphan*/  MVPP22_FLOW_IP4 ; 
 int /*<<< orphan*/  MVPP22_FLOW_IP6 ; 
 int /*<<< orphan*/  MVPP22_FLOW_TCP4 ; 
 int /*<<< orphan*/  MVPP22_FLOW_TCP6 ; 
 int /*<<< orphan*/  MVPP22_FLOW_UDP4 ; 
 int /*<<< orphan*/  MVPP22_FLOW_UDP6 ; 
 int MVPP22_N_RSS_TABLES ; 
 int MVPP22_RSS_TABLE_ENTRIES ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 int mvpp22_rss_context_create (struct mvpp2_port*,int*) ; 
 int /*<<< orphan*/  mvpp22_rss_ctx (struct mvpp2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp22_rss_fill_table (struct mvpp2_port*,struct mvpp2_rss_table*,int /*<<< orphan*/ ) ; 
 struct mvpp2_rss_table* mvpp22_rss_table_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_port_rss_hash_opts_set (struct mvpp2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mvpp22_port_rss_init(struct mvpp2_port *port)
{
	struct mvpp2_rss_table *table;
	u32 context = 0;
	int i, ret;

	for (i = 0; i < MVPP22_N_RSS_TABLES; i++)
		port->rss_ctx[i] = -1;

	ret = mvpp22_rss_context_create(port, &context);
	if (ret)
		return ret;

	table = mvpp22_rss_table_get(port->priv, context);
	if (!table)
		return -EINVAL;

	port->rss_ctx[0] = context;

	/* Configure the first table to evenly distribute the packets across
	 * real Rx Queues. The table entries map a hash to a port Rx Queue.
	 */
	for (i = 0; i < MVPP22_RSS_TABLE_ENTRIES; i++)
		table->indir[i] = ethtool_rxfh_indir_default(i, port->nrxqs);

	mvpp22_rss_fill_table(port, table, mvpp22_rss_ctx(port, 0));

	/* Configure default flows */
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_IP4, MVPP22_CLS_HEK_IP4_2T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_IP6, MVPP22_CLS_HEK_IP6_2T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_TCP4, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_TCP6, MVPP22_CLS_HEK_IP6_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_UDP4, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, MVPP22_FLOW_UDP6, MVPP22_CLS_HEK_IP6_5T);

	return 0;
}