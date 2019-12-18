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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nfp_police_cfg_head {int /*<<< orphan*/  port; } ;
struct nfp_flower_priv {TYPE_1__* app; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_QOS_STATS ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfp_police_cfg_head*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nfp_police_cfg_head* nfp_flower_cmsg_get_data (struct sk_buff*) ; 

__attribute__((used)) static void
nfp_flower_stats_rlim_request(struct nfp_flower_priv *fl_priv,
			      u32 netdev_port_id)
{
	struct nfp_police_cfg_head *head;
	struct sk_buff *skb;

	skb = nfp_flower_cmsg_alloc(fl_priv->app,
				    sizeof(struct nfp_police_cfg_head),
				    NFP_FLOWER_CMSG_TYPE_QOS_STATS,
				    GFP_ATOMIC);
	if (!skb)
		return;

	head = nfp_flower_cmsg_get_data(skb);
	memset(head, 0, sizeof(struct nfp_police_cfg_head));
	head->port = cpu_to_be32(netdev_port_id);

	nfp_ctrl_tx(fl_priv->app->ctrl, skb);
}