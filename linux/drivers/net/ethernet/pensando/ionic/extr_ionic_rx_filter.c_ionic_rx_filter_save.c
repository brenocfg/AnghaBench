#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_13__ {int /*<<< orphan*/  vlan; } ;
struct TYPE_12__ {scalar_t__ addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  vlan; } ;
struct ionic_rx_filter_add_cmd {TYPE_5__ mac_vlan; TYPE_4__ mac; TYPE_3__ vlan; int /*<<< orphan*/  match; } ;
struct ionic_rx_filter {unsigned int filter_id; int /*<<< orphan*/  by_id; int /*<<< orphan*/  by_hash; int /*<<< orphan*/  cmd; int /*<<< orphan*/  rxq_index; void* flow_id; } ;
struct TYPE_16__ {int /*<<< orphan*/  lock; struct hlist_head* by_id; struct hlist_head* by_hash; } ;
struct ionic_lif {TYPE_8__ rx_filters; TYPE_1__* ionic; } ;
struct TYPE_14__ {int /*<<< orphan*/  filter_id; } ;
struct TYPE_15__ {TYPE_6__ rx_filter_add; } ;
struct TYPE_10__ {struct ionic_rx_filter_add_cmd rx_filter_add; } ;
struct ionic_admin_ctx {TYPE_7__ comp; TYPE_2__ cmd; } ;
struct hlist_head {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_9__ {struct device* dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IONIC_RX_FILTER_HASH_BITS ; 
 unsigned int IONIC_RX_FILTER_HLISTS_MASK ; 
#define  IONIC_RX_FILTER_MATCH_MAC 130 
#define  IONIC_RX_FILTER_MATCH_MAC_VLAN 129 
#define  IONIC_RX_FILTER_MATCH_VLAN 128 
 struct ionic_rx_filter* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 unsigned int hash_32 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ionic_rx_filter_add_cmd*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int ionic_rx_filter_save(struct ionic_lif *lif, u32 flow_id, u16 rxq_index,
			 u32 hash, struct ionic_admin_ctx *ctx)
{
	struct device *dev = lif->ionic->dev;
	struct ionic_rx_filter_add_cmd *ac;
	struct ionic_rx_filter *f;
	struct hlist_head *head;
	unsigned int key;

	ac = &ctx->cmd.rx_filter_add;

	switch (le16_to_cpu(ac->match)) {
	case IONIC_RX_FILTER_MATCH_VLAN:
		key = le16_to_cpu(ac->vlan.vlan);
		break;
	case IONIC_RX_FILTER_MATCH_MAC:
		key = *(u32 *)ac->mac.addr;
		break;
	case IONIC_RX_FILTER_MATCH_MAC_VLAN:
		key = le16_to_cpu(ac->mac_vlan.vlan);
		break;
	default:
		return -EINVAL;
	}

	f = devm_kzalloc(dev, sizeof(*f), GFP_KERNEL);
	if (!f)
		return -ENOMEM;

	f->flow_id = flow_id;
	f->filter_id = le32_to_cpu(ctx->comp.rx_filter_add.filter_id);
	f->rxq_index = rxq_index;
	memcpy(&f->cmd, ac, sizeof(f->cmd));

	INIT_HLIST_NODE(&f->by_hash);
	INIT_HLIST_NODE(&f->by_id);

	spin_lock_bh(&lif->rx_filters.lock);

	key = hash_32(key, IONIC_RX_FILTER_HASH_BITS);
	head = &lif->rx_filters.by_hash[key];
	hlist_add_head(&f->by_hash, head);

	key = f->filter_id & IONIC_RX_FILTER_HLISTS_MASK;
	head = &lif->rx_filters.by_id[key];
	hlist_add_head(&f->by_id, head);

	spin_unlock_bh(&lif->rx_filters.lock);

	return 0;
}