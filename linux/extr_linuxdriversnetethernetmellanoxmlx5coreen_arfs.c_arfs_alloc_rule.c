#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ protocol; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_filter_id; } ;
struct TYPE_6__ {TYPE_1__ arfs; } ;
struct mlx5e_priv {TYPE_2__ fs; } ;
struct in6_addr {int dummy; } ;
struct arfs_tuple {scalar_t__ etype; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  ip_proto; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/  src_ipv4; } ;
struct arfs_table {int dummy; } ;
struct arfs_rule {int filter_id; int /*<<< orphan*/  hlist; int /*<<< orphan*/  flow_id; struct arfs_tuple tuple; int /*<<< orphan*/  arfs_work; int /*<<< orphan*/  rxq; struct mlx5e_priv* priv; } ;
struct TYPE_8__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;
struct TYPE_7__ {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RPS_NO_FILTER ; 
 int /*<<< orphan*/  arfs_get_dst_port (struct sk_buff const*) ; 
 int /*<<< orphan*/  arfs_get_ip_proto (struct sk_buff const*) ; 
 int /*<<< orphan*/  arfs_get_src_port (struct sk_buff const*) ; 
 int /*<<< orphan*/  arfs_handle_work ; 
 int /*<<< orphan*/  arfs_hash_bucket (struct arfs_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_4__* ip_hdr (struct sk_buff const*) ; 
 TYPE_3__* ipv6_hdr (struct sk_buff const*) ; 
 struct arfs_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct arfs_rule *arfs_alloc_rule(struct mlx5e_priv *priv,
					 struct arfs_table *arfs_t,
					 const struct sk_buff *skb,
					 u16 rxq, u32 flow_id)
{
	struct arfs_rule *rule;
	struct arfs_tuple *tuple;

	rule = kzalloc(sizeof(*rule), GFP_ATOMIC);
	if (!rule)
		return NULL;

	rule->priv = priv;
	rule->rxq = rxq;
	INIT_WORK(&rule->arfs_work, arfs_handle_work);

	tuple = &rule->tuple;
	tuple->etype = skb->protocol;
	if (tuple->etype == htons(ETH_P_IP)) {
		tuple->src_ipv4 = ip_hdr(skb)->saddr;
		tuple->dst_ipv4 = ip_hdr(skb)->daddr;
	} else {
		memcpy(&tuple->src_ipv6, &ipv6_hdr(skb)->saddr,
		       sizeof(struct in6_addr));
		memcpy(&tuple->dst_ipv6, &ipv6_hdr(skb)->daddr,
		       sizeof(struct in6_addr));
	}
	tuple->ip_proto = arfs_get_ip_proto(skb);
	tuple->src_port = arfs_get_src_port(skb);
	tuple->dst_port = arfs_get_dst_port(skb);

	rule->flow_id = flow_id;
	rule->filter_id = priv->fs.arfs.last_filter_id++ % RPS_NO_FILTER;

	hlist_add_head(&rule->hlist,
		       arfs_hash_bucket(arfs_t, tuple->src_port,
					tuple->dst_port));
	return rule;
}