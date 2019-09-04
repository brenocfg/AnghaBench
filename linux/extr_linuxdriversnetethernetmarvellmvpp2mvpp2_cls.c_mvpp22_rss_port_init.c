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
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  nrxqs; int /*<<< orphan*/ * indir; int /*<<< orphan*/  first_rxq; struct mvpp2* priv; } ;
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPV4_FLOW ; 
 int /*<<< orphan*/  IPV6_FLOW ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP4_2T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP4_5T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP6_2T ; 
 int /*<<< orphan*/  MVPP22_CLS_HEK_IP6_5T ; 
 int /*<<< orphan*/  MVPP22_RSS_INDEX ; 
 int MVPP22_RSS_INDEX_QUEUE (int /*<<< orphan*/ ) ; 
 int MVPP22_RSS_INDEX_TABLE (int /*<<< orphan*/ ) ; 
 int MVPP22_RSS_TABLE_ENTRIES ; 
 int MVPP22_RSS_TABLE_POINTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP22_RSS_WIDTH ; 
 int /*<<< orphan*/  MVPP22_RXQ2RSS_TABLE ; 
 int /*<<< orphan*/  TCP_V4_FLOW ; 
 int /*<<< orphan*/  TCP_V6_FLOW ; 
 int /*<<< orphan*/  UDP_V4_FLOW ; 
 int /*<<< orphan*/  UDP_V6_FLOW ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp22_rss_fill_table (struct mvpp2_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_port_rss_hash_opts_set (struct mvpp2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

void mvpp22_rss_port_init(struct mvpp2_port *port)
{
	struct mvpp2 *priv = port->priv;
	int i;

	/* Set the table width: replace the whole classifier Rx queue number
	 * with the ones configured in RSS table entries.
	 */
	mvpp2_write(priv, MVPP22_RSS_INDEX, MVPP22_RSS_INDEX_TABLE(port->id));
	mvpp2_write(priv, MVPP22_RSS_WIDTH, 8);

	/* The default RxQ is used as a key to select the RSS table to use.
	 * We use one RSS table per port.
	 */
	mvpp2_write(priv, MVPP22_RSS_INDEX,
		    MVPP22_RSS_INDEX_QUEUE(port->first_rxq));
	mvpp2_write(priv, MVPP22_RXQ2RSS_TABLE,
		    MVPP22_RSS_TABLE_POINTER(port->id));

	/* Configure the first table to evenly distribute the packets across
	 * real Rx Queues. The table entries map a hash to a port Rx Queue.
	 */
	for (i = 0; i < MVPP22_RSS_TABLE_ENTRIES; i++)
		port->indir[i] = ethtool_rxfh_indir_default(i, port->nrxqs);

	mvpp22_rss_fill_table(port, port->id);

	/* Configure default flows */
	mvpp2_port_rss_hash_opts_set(port, IPV4_FLOW, MVPP22_CLS_HEK_IP4_2T);
	mvpp2_port_rss_hash_opts_set(port, IPV6_FLOW, MVPP22_CLS_HEK_IP6_2T);
	mvpp2_port_rss_hash_opts_set(port, TCP_V4_FLOW, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, TCP_V6_FLOW, MVPP22_CLS_HEK_IP6_5T);
	mvpp2_port_rss_hash_opts_set(port, UDP_V4_FLOW, MVPP22_CLS_HEK_IP4_5T);
	mvpp2_port_rss_hash_opts_set(port, UDP_V6_FLOW, MVPP22_CLS_HEK_IP6_5T);
}