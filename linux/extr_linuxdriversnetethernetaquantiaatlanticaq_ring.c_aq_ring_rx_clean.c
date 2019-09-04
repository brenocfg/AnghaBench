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
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct napi_struct {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct aq_ring_s {size_t sw_head; size_t hw_head; TYPE_2__ stats; int /*<<< orphan*/  idx; struct aq_ring_buff_s* buff_ring; int /*<<< orphan*/  aq_nic; } ;
struct aq_ring_buff_s {int is_cleaned; unsigned int next; scalar_t__ len; scalar_t__ is_hash_l4; int /*<<< orphan*/  rss_hash; scalar_t__ is_eop; int /*<<< orphan*/  page; scalar_t__ is_error; } ;

/* Variables and functions */
 scalar_t__ AQ_CFG_RX_FRAME_MAX ; 
 scalar_t__ AQ_SKB_ALIGN ; 
 int ENOMEM ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_L4 ; 
 int /*<<< orphan*/  PKT_HASH_TYPE_NONE ; 
 int /*<<< orphan*/  SKB_TRUESIZE (scalar_t__) ; 
 int /*<<< orphan*/  __free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* aq_nic_get_ndev (int /*<<< orphan*/ ) ; 
 int aq_ring_dx_in_range (size_t,unsigned int,size_t) ; 
 size_t aq_ring_next_dx (struct aq_ring_s*,size_t) ; 
 int /*<<< orphan*/  aq_rx_checksum (struct aq_ring_s*,struct aq_ring_buff_s*,struct sk_buff*) ; 
 struct sk_buff* build_skb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,unsigned int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int aq_ring_rx_clean(struct aq_ring_s *self,
		     struct napi_struct *napi,
		     int *work_done,
		     int budget)
{
	struct net_device *ndev = aq_nic_get_ndev(self->aq_nic);
	int err = 0;
	bool is_rsc_completed = true;

	for (; (self->sw_head != self->hw_head) && budget;
		self->sw_head = aq_ring_next_dx(self, self->sw_head),
		--budget, ++(*work_done)) {
		struct aq_ring_buff_s *buff = &self->buff_ring[self->sw_head];
		struct sk_buff *skb = NULL;
		unsigned int next_ = 0U;
		unsigned int i = 0U;
		struct aq_ring_buff_s *buff_ = NULL;

		if (buff->is_error) {
			__free_pages(buff->page, 0);
			continue;
		}

		if (buff->is_cleaned)
			continue;

		if (!buff->is_eop) {
			for (next_ = buff->next,
			     buff_ = &self->buff_ring[next_]; true;
			     next_ = buff_->next,
			     buff_ = &self->buff_ring[next_]) {
				is_rsc_completed =
					aq_ring_dx_in_range(self->sw_head,
							    next_,
							    self->hw_head);

				if (unlikely(!is_rsc_completed)) {
					is_rsc_completed = false;
					break;
				}

				if (buff_->is_eop)
					break;
			}

			if (!is_rsc_completed) {
				err = 0;
				goto err_exit;
			}
		}

		/* for single fragment packets use build_skb() */
		if (buff->is_eop &&
		    buff->len <= AQ_CFG_RX_FRAME_MAX - AQ_SKB_ALIGN) {
			skb = build_skb(page_address(buff->page),
					AQ_CFG_RX_FRAME_MAX);
			if (unlikely(!skb)) {
				err = -ENOMEM;
				goto err_exit;
			}

			skb_put(skb, buff->len);
		} else {
			skb = netdev_alloc_skb(ndev, ETH_HLEN);
			if (unlikely(!skb)) {
				err = -ENOMEM;
				goto err_exit;
			}
			skb_put(skb, ETH_HLEN);
			memcpy(skb->data, page_address(buff->page), ETH_HLEN);

			skb_add_rx_frag(skb, 0, buff->page, ETH_HLEN,
					buff->len - ETH_HLEN,
					SKB_TRUESIZE(buff->len - ETH_HLEN));

			if (!buff->is_eop) {
				for (i = 1U, next_ = buff->next,
				     buff_ = &self->buff_ring[next_];
				     true; next_ = buff_->next,
				     buff_ = &self->buff_ring[next_], ++i) {
					skb_add_rx_frag(skb, i,
							buff_->page, 0,
							buff_->len,
							SKB_TRUESIZE(buff->len -
							ETH_HLEN));
					buff_->is_cleaned = 1;

					if (buff_->is_eop)
						break;
				}
			}
		}

		skb->protocol = eth_type_trans(skb, ndev);

		aq_rx_checksum(self, buff, skb);

		skb_set_hash(skb, buff->rss_hash,
			     buff->is_hash_l4 ? PKT_HASH_TYPE_L4 :
			     PKT_HASH_TYPE_NONE);

		skb_record_rx_queue(skb, self->idx);

		++self->stats.rx.packets;
		self->stats.rx.bytes += skb->len;

		napi_gro_receive(napi, skb);
	}

err_exit:
	return err;
}