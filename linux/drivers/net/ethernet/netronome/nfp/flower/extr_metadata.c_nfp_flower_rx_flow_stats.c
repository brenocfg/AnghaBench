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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct nfp_flower_priv {int /*<<< orphan*/  stats_lock; TYPE_1__* stats; } ;
struct nfp_fl_stats_frame {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  pkt_count; int /*<<< orphan*/  stats_con_id; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  used; int /*<<< orphan*/  bytes; int /*<<< orphan*/  pkts; } ;

/* Variables and functions */
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned char* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 unsigned int nfp_flower_cmsg_get_data_len (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfp_flower_rx_flow_stats(struct nfp_app *app, struct sk_buff *skb)
{
	unsigned int msg_len = nfp_flower_cmsg_get_data_len(skb);
	struct nfp_flower_priv *priv = app->priv;
	struct nfp_fl_stats_frame *stats;
	unsigned char *msg;
	u32 ctx_id;
	int i;

	msg = nfp_flower_cmsg_get_data(skb);

	spin_lock(&priv->stats_lock);
	for (i = 0; i < msg_len / sizeof(*stats); i++) {
		stats = (struct nfp_fl_stats_frame *)msg + i;
		ctx_id = be32_to_cpu(stats->stats_con_id);
		priv->stats[ctx_id].pkts += be32_to_cpu(stats->pkt_count);
		priv->stats[ctx_id].bytes += be64_to_cpu(stats->byte_count);
		priv->stats[ctx_id].used = jiffies;
	}
	spin_unlock(&priv->stats_lock);
}