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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {struct sk_buff* next; scalar_t__ len; scalar_t__ data; } ;
struct htt_rx_in_ord_msdu_desc_ext {int /*<<< orphan*/  msdu_len; scalar_t__ reserved; int /*<<< orphan*/  msdu_paddr; } ;
struct htt_rx_desc {int dummy; } ;
struct ath10k_htt {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  HTT_RX_BUF_SIZE ; 
 int /*<<< orphan*/  HTT_RX_MSDU_SIZE ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_htt_append_frag_list (struct sk_buff*,struct sk_buff*,int) ; 
 struct sk_buff* ath10k_htt_rx_pop_paddr (struct ath10k_htt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_ath10k_htt_rx_desc (struct ath10k*,struct htt_rx_desc*,int) ; 

__attribute__((used)) static int
ath10k_htt_rx_handle_amsdu_mon_64(struct ath10k_htt *htt,
				  struct sk_buff *msdu,
				  struct htt_rx_in_ord_msdu_desc_ext **msdu_desc)
{
	struct ath10k *ar = htt->ar;
	u64 paddr;
	struct sk_buff *frag_buf;
	struct sk_buff *prev_frag_buf;
	u8 last_frag;
	struct htt_rx_in_ord_msdu_desc_ext *ind_desc = *msdu_desc;
	struct htt_rx_desc *rxd;
	int amsdu_len = __le16_to_cpu(ind_desc->msdu_len);

	rxd = (void *)msdu->data;
	trace_ath10k_htt_rx_desc(ar, rxd, sizeof(*rxd));

	skb_put(msdu, sizeof(struct htt_rx_desc));
	skb_pull(msdu, sizeof(struct htt_rx_desc));
	skb_put(msdu, min(amsdu_len, HTT_RX_MSDU_SIZE));
	amsdu_len -= msdu->len;

	last_frag = ind_desc->reserved;
	if (last_frag) {
		if (amsdu_len) {
			ath10k_warn(ar, "invalid amsdu len %u, left %d",
				    __le16_to_cpu(ind_desc->msdu_len),
				    amsdu_len);
		}
		return 0;
	}

	ind_desc++;
	paddr = __le64_to_cpu(ind_desc->msdu_paddr);
	frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
	if (!frag_buf) {
		ath10k_warn(ar, "failed to pop frag-1 paddr: 0x%llx", paddr);
		return -ENOENT;
	}

	skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
	ath10k_htt_append_frag_list(msdu, frag_buf, amsdu_len);

	amsdu_len -= frag_buf->len;
	prev_frag_buf = frag_buf;
	last_frag = ind_desc->reserved;
	while (!last_frag) {
		ind_desc++;
		paddr = __le64_to_cpu(ind_desc->msdu_paddr);
		frag_buf = ath10k_htt_rx_pop_paddr(htt, paddr);
		if (!frag_buf) {
			ath10k_warn(ar, "failed to pop frag-n paddr: 0x%llx",
				    paddr);
			prev_frag_buf->next = NULL;
			return -ENOENT;
		}

		skb_put(frag_buf, min(amsdu_len, HTT_RX_BUF_SIZE));
		last_frag = ind_desc->reserved;
		amsdu_len -= frag_buf->len;

		prev_frag_buf->next = frag_buf;
		prev_frag_buf = frag_buf;
	}

	if (amsdu_len) {
		ath10k_warn(ar, "invalid amsdu len %u, left %d",
			    __le16_to_cpu(ind_desc->msdu_len), amsdu_len);
	}

	*msdu_desc = ind_desc;

	prev_frag_buf->next = NULL;
	return 0;
}