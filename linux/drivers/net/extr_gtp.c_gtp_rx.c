#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; TYPE_1__* dev; int /*<<< orphan*/  protocol; } ;
struct pdp_ctx {TYPE_1__* dev; int /*<<< orphan*/  sk; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  tstats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_net (TYPE_1__*) ; 
 int /*<<< orphan*/  gtp_check_ms (struct sk_buff*,struct pdp_ctx*,unsigned int,unsigned int) ; 
 scalar_t__ iptunnel_pull_header (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gtp_rx(struct pdp_ctx *pctx, struct sk_buff *skb,
			unsigned int hdrlen, unsigned int role)
{
	struct pcpu_sw_netstats *stats;

	if (!gtp_check_ms(skb, pctx, hdrlen, role)) {
		netdev_dbg(pctx->dev, "No PDP ctx for this MS\n");
		return 1;
	}

	/* Get rid of the GTP + UDP headers. */
	if (iptunnel_pull_header(skb, hdrlen, skb->protocol,
				 !net_eq(sock_net(pctx->sk), dev_net(pctx->dev))))
		return -1;

	netdev_dbg(pctx->dev, "forwarding packet from GGSN to uplink\n");

	/* Now that the UDP and the GTP header have been removed, set up the
	 * new network header. This is required by the upper layer to
	 * calculate the transport header.
	 */
	skb_reset_network_header(skb);

	skb->dev = pctx->dev;

	stats = this_cpu_ptr(pctx->dev->tstats);
	u64_stats_update_begin(&stats->syncp);
	stats->rx_packets++;
	stats->rx_bytes += skb->len;
	u64_stats_update_end(&stats->syncp);

	netif_rx(skb);
	return 0;
}