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
struct sk_buff_head {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nfp_flower_priv {int /*<<< orphan*/  cmsg_work; struct sk_buff_head cmsg_skbs_low; struct sk_buff_head cmsg_skbs_high; } ;
struct nfp_app {struct nfp_flower_priv* priv; } ;

/* Variables and functions */
 int NFP_FLOWER_CMSG_TYPE_PORT_MOD ; 
 scalar_t__ NFP_FLOWER_WORKQ_MAX_SKBS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_warn (struct nfp_app*,char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 

__attribute__((used)) static void
nfp_flower_queue_ctl_msg(struct nfp_app *app, struct sk_buff *skb, int type)
{
	struct nfp_flower_priv *priv = app->priv;
	struct sk_buff_head *skb_head;

	if (type == NFP_FLOWER_CMSG_TYPE_PORT_MOD)
		skb_head = &priv->cmsg_skbs_high;
	else
		skb_head = &priv->cmsg_skbs_low;

	if (skb_queue_len(skb_head) >= NFP_FLOWER_WORKQ_MAX_SKBS) {
		nfp_flower_cmsg_warn(app, "Dropping queued control messages\n");
		dev_kfree_skb_any(skb);
		return;
	}

	skb_queue_tail(skb_head, skb);
	schedule_work(&priv->cmsg_work);
}