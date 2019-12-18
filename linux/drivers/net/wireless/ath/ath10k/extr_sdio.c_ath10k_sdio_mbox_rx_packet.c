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
struct sk_buff {scalar_t__ data; } ;
struct ath10k_sdio_rx_data {int status; scalar_t__ act_len; scalar_t__ alloc_len; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  htc_addr; } ;
struct ath10k_sdio {TYPE_1__ mbox_info; } ;
struct ath10k_htc_hdr {int /*<<< orphan*/  len; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 struct ath10k_sdio* ath10k_sdio_priv (struct ath10k*) ; 
 int ath10k_sdio_readsb (struct ath10k*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,scalar_t__) ; 

__attribute__((used)) static int ath10k_sdio_mbox_rx_packet(struct ath10k *ar,
				      struct ath10k_sdio_rx_data *pkt)
{
	struct ath10k_sdio *ar_sdio = ath10k_sdio_priv(ar);
	struct sk_buff *skb = pkt->skb;
	struct ath10k_htc_hdr *htc_hdr;
	int ret;

	ret = ath10k_sdio_readsb(ar, ar_sdio->mbox_info.htc_addr,
				 skb->data, pkt->alloc_len);
	if (ret)
		goto out;

	/* Update actual length. The original length may be incorrect,
	 * as the FW will bundle multiple packets as long as their sizes
	 * fit within the same aligned length (pkt->alloc_len).
	 */
	htc_hdr = (struct ath10k_htc_hdr *)skb->data;
	pkt->act_len = le16_to_cpu(htc_hdr->len) + sizeof(*htc_hdr);
	if (pkt->act_len > pkt->alloc_len) {
		ath10k_warn(ar, "rx packet too large (%zu > %zu)\n",
			    pkt->act_len, pkt->alloc_len);
		ret = -EMSGSIZE;
		goto out;
	}

	skb_put(skb, pkt->act_len);

out:
	pkt->status = ret;

	return ret;
}