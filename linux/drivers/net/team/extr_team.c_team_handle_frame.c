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
struct team_port {struct team* team; } ;
struct team_pcpu_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_3__ {scalar_t__ (* receive ) (struct team*,struct team_port*,struct sk_buff*) ;} ;
struct team {TYPE_2__* pcpu_stats; int /*<<< orphan*/  dev; TYPE_1__ ops; } ;
struct sk_buff {scalar_t__ pkt_type; int /*<<< orphan*/  dev; scalar_t__ len; } ;
typedef  scalar_t__ rx_handler_result_t ;
struct TYPE_4__ {int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_nohandler; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ PACKET_MULTICAST ; 
 scalar_t__ RX_HANDLER_ANOTHER ; 
 scalar_t__ RX_HANDLER_CONSUMED ; 
 scalar_t__ RX_HANDLER_EXACT ; 
 struct sk_buff* skb_share_check (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct team*,struct team_port*,struct sk_buff*) ; 
 int /*<<< orphan*/  team_port_enabled (struct team_port*) ; 
 struct team_port* team_port_get_rcu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct team_pcpu_stats* this_cpu_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rx_handler_result_t team_handle_frame(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct team_port *port;
	struct team *team;
	rx_handler_result_t res;

	skb = skb_share_check(skb, GFP_ATOMIC);
	if (!skb)
		return RX_HANDLER_CONSUMED;

	*pskb = skb;

	port = team_port_get_rcu(skb->dev);
	team = port->team;
	if (!team_port_enabled(port)) {
		/* allow exact match delivery for disabled ports */
		res = RX_HANDLER_EXACT;
	} else {
		res = team->ops.receive(team, port, skb);
	}
	if (res == RX_HANDLER_ANOTHER) {
		struct team_pcpu_stats *pcpu_stats;

		pcpu_stats = this_cpu_ptr(team->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->rx_packets++;
		pcpu_stats->rx_bytes += skb->len;
		if (skb->pkt_type == PACKET_MULTICAST)
			pcpu_stats->rx_multicast++;
		u64_stats_update_end(&pcpu_stats->syncp);

		skb->dev = team->dev;
	} else if (res == RX_HANDLER_EXACT) {
		this_cpu_inc(team->pcpu_stats->rx_nohandler);
	} else {
		this_cpu_inc(team->pcpu_stats->rx_dropped);
	}

	return res;
}