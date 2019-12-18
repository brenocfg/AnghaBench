#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  seg_pkt_cnt; int /*<<< orphan*/  sw_err_cnt; } ;
struct hns3_enet_ring {size_t next_to_clean; int pending_buf; unsigned int pull_len; scalar_t__ frag_num; int /*<<< orphan*/  syncp; TYPE_5__ stats; int /*<<< orphan*/ * tail_skb; struct sk_buff* skb; TYPE_4__* tqp_vector; TYPE_3__* tqp; struct hns3_desc_cb* desc_cb; } ;
struct hns3_desc_cb {int reuse_flag; int /*<<< orphan*/  priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  napi; } ;
struct TYPE_8__ {TYPE_2__* handle; } ;
struct TYPE_6__ {struct net_device* netdev; } ;
struct TYPE_7__ {TYPE_1__ kinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (unsigned int,int) ; 
 int ENOMEM ; 
 int HNS3_NEED_ADD_FRAG ; 
 unsigned int HNS3_RX_HEAD_SIZE ; 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 unsigned int eth_get_headlen (struct net_device*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  hns3_nic_reuse_page (struct sk_buff*,int /*<<< orphan*/ ,struct hns3_enet_ring*,unsigned int,struct hns3_desc_cb*) ; 
 int /*<<< orphan*/  hns3_rl_err (struct net_device*,char*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 struct sk_buff* napi_alloc_skb (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  next_to_clean ; 
 scalar_t__ numa_mem_id () ; 
 scalar_t__ page_to_nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ring_ptr_move_fw (struct hns3_enet_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hns3_alloc_skb(struct hns3_enet_ring *ring, unsigned int length,
			  unsigned char *va)
{
#define HNS3_NEED_ADD_FRAG	1
	struct hns3_desc_cb *desc_cb = &ring->desc_cb[ring->next_to_clean];
	struct net_device *netdev = ring->tqp->handle->kinfo.netdev;
	struct sk_buff *skb;

	ring->skb = napi_alloc_skb(&ring->tqp_vector->napi, HNS3_RX_HEAD_SIZE);
	skb = ring->skb;
	if (unlikely(!skb)) {
		hns3_rl_err(netdev, "alloc rx skb fail\n");

		u64_stats_update_begin(&ring->syncp);
		ring->stats.sw_err_cnt++;
		u64_stats_update_end(&ring->syncp);

		return -ENOMEM;
	}

	prefetchw(skb->data);

	ring->pending_buf = 1;
	ring->frag_num = 0;
	ring->tail_skb = NULL;
	if (length <= HNS3_RX_HEAD_SIZE) {
		memcpy(__skb_put(skb, length), va, ALIGN(length, sizeof(long)));

		/* We can reuse buffer as-is, just make sure it is local */
		if (likely(page_to_nid(desc_cb->priv) == numa_mem_id()))
			desc_cb->reuse_flag = 1;
		else /* This page cannot be reused so discard it */
			put_page(desc_cb->priv);

		ring_ptr_move_fw(ring, next_to_clean);
		return 0;
	}
	u64_stats_update_begin(&ring->syncp);
	ring->stats.seg_pkt_cnt++;
	u64_stats_update_end(&ring->syncp);

	ring->pull_len = eth_get_headlen(netdev, va, HNS3_RX_HEAD_SIZE);
	__skb_put(skb, ring->pull_len);
	hns3_nic_reuse_page(skb, ring->frag_num++, ring, ring->pull_len,
			    desc_cb);
	ring_ptr_move_fw(ring, next_to_clean);

	return HNS3_NEED_ADD_FRAG;
}