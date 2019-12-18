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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct htt_rx_in_ord_msdu_desc_ext {int /*<<< orphan*/  msdu_len; int /*<<< orphan*/  msdu_paddr; } ;
struct htt_rx_in_ord_ind {int info; int /*<<< orphan*/  msdu_count; struct htt_rx_in_ord_msdu_desc_ext* msdu_descs64; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct htt_rx_desc {TYPE_2__ attention; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct ath10k_htt {struct ath10k* ar; TYPE_1__ rx_ring; } ;
struct ath10k {scalar_t__ monitor_arvif; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK ; 
 int RX_ATTENTION_FLAGS_MSDU_DONE ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_purge (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int ath10k_htt_rx_handle_amsdu_mon_64 (struct ath10k_htt*,struct sk_buff*,struct htt_rx_in_ord_msdu_desc_ext**) ; 
 struct sk_buff* ath10k_htt_rx_pop_paddr (struct ath10k_htt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_ath10k_htt_rx_desc (struct ath10k*,struct htt_rx_desc*,int) ; 

__attribute__((used)) static int ath10k_htt_rx_pop_paddr64_list(struct ath10k_htt *htt,
					  struct htt_rx_in_ord_ind *ev,
					  struct sk_buff_head *list)
{
	struct ath10k *ar = htt->ar;
	struct htt_rx_in_ord_msdu_desc_ext *msdu_desc = ev->msdu_descs64;
	struct htt_rx_desc *rxd;
	struct sk_buff *msdu;
	int msdu_count, ret;
	bool is_offload;
	u64 paddr;

	lockdep_assert_held(&htt->rx_ring.lock);

	msdu_count = __le16_to_cpu(ev->msdu_count);
	is_offload = !!(ev->info & HTT_RX_IN_ORD_IND_INFO_OFFLOAD_MASK);

	while (msdu_count--) {
		paddr = __le64_to_cpu(msdu_desc->msdu_paddr);
		msdu = ath10k_htt_rx_pop_paddr(htt, paddr);
		if (!msdu) {
			__skb_queue_purge(list);
			return -ENOENT;
		}

		if (!is_offload && ar->monitor_arvif) {
			ret = ath10k_htt_rx_handle_amsdu_mon_64(htt, msdu,
								&msdu_desc);
			if (ret) {
				__skb_queue_purge(list);
				return ret;
			}
			__skb_queue_tail(list, msdu);
			msdu_desc++;
			continue;
		}

		__skb_queue_tail(list, msdu);

		if (!is_offload) {
			rxd = (void *)msdu->data;

			trace_ath10k_htt_rx_desc(ar, rxd, sizeof(*rxd));

			skb_put(msdu, sizeof(*rxd));
			skb_pull(msdu, sizeof(*rxd));
			skb_put(msdu, __le16_to_cpu(msdu_desc->msdu_len));

			if (!(__le32_to_cpu(rxd->attention.flags) &
			      RX_ATTENTION_FLAGS_MSDU_DONE)) {
				ath10k_warn(htt->ar, "tried to pop an incomplete frame, oops!\n");
				return -EIO;
			}
		}

		msdu_desc++;
	}

	return 0;
}