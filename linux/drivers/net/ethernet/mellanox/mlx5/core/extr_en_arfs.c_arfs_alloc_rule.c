#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_13__ {int /*<<< orphan*/  last_filter_id; } ;
struct TYPE_14__ {TYPE_6__ arfs; } ;
struct mlx5e_priv {TYPE_7__ fs; } ;
struct in6_addr {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_10__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_9__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_11__ {TYPE_3__ v6addrs; TYPE_2__ v4addrs; } ;
struct TYPE_8__ {scalar_t__ n_proto; int /*<<< orphan*/  ip_proto; } ;
struct flow_keys {TYPE_5__ ports; TYPE_4__ addrs; TYPE_1__ basic; } ;
struct arfs_tuple {scalar_t__ etype; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; int /*<<< orphan*/  dst_ipv6; int /*<<< orphan*/  src_ipv6; int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/  src_ipv4; int /*<<< orphan*/  ip_proto; } ;
struct arfs_table {int dummy; } ;
struct arfs_rule {int filter_id; int /*<<< orphan*/  hlist; int /*<<< orphan*/  flow_id; struct arfs_tuple tuple; int /*<<< orphan*/  arfs_work; int /*<<< orphan*/  rxq; struct mlx5e_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int RPS_NO_FILTER ; 
 int /*<<< orphan*/  arfs_handle_work ; 
 int /*<<< orphan*/  arfs_hash_bucket (struct arfs_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct arfs_rule* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct arfs_rule *arfs_alloc_rule(struct mlx5e_priv *priv,
					 struct arfs_table *arfs_t,
					 const struct flow_keys *fk,
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
	tuple->etype = fk->basic.n_proto;
	tuple->ip_proto = fk->basic.ip_proto;
	if (tuple->etype == htons(ETH_P_IP)) {
		tuple->src_ipv4 = fk->addrs.v4addrs.src;
		tuple->dst_ipv4 = fk->addrs.v4addrs.dst;
	} else {
		memcpy(&tuple->src_ipv6, &fk->addrs.v6addrs.src,
		       sizeof(struct in6_addr));
		memcpy(&tuple->dst_ipv6, &fk->addrs.v6addrs.dst,
		       sizeof(struct in6_addr));
	}
	tuple->src_port = fk->ports.src;
	tuple->dst_port = fk->ports.dst;

	rule->flow_id = flow_id;
	rule->filter_id = priv->fs.arfs.last_filter_id++ % RPS_NO_FILTER;

	hlist_add_head(&rule->hlist,
		       arfs_hash_bucket(arfs_t, tuple->src_port,
					tuple->dst_port));
	return rule;
}