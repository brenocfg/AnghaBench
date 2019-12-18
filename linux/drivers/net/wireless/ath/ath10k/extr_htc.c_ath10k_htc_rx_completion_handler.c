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
typedef  size_t u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k_htc_hdr {size_t eid; int flags; size_t trailer_len; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ep_rx_complete ) (struct ath10k*,struct sk_buff*) ;} ;
struct ath10k_htc_ep {TYPE_1__ ep_ops; } ;
struct ath10k_htc {struct ath10k_htc_ep* endpoint; } ;
struct ath10k_ath10k_htc_record_hdr {int dummy; } ;
struct ath10k {struct ath10k_htc htc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTC ; 
 size_t ATH10K_HTC_EP_COUNT ; 
 int ATH10K_HTC_FLAG_TRAILER_PRESENT ; 
 int ATH10K_HTC_MAX_LEN ; 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  ath10k_dbg_dump (struct ath10k*,int /*<<< orphan*/ ,char*,char*,struct ath10k_htc_hdr*,int) ; 
 int ath10k_htc_process_trailer (struct ath10k_htc*,size_t*,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,size_t) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*,struct sk_buff*) ; 

void ath10k_htc_rx_completion_handler(struct ath10k *ar, struct sk_buff *skb)
{
	int status = 0;
	struct ath10k_htc *htc = &ar->htc;
	struct ath10k_htc_hdr *hdr;
	struct ath10k_htc_ep *ep;
	u16 payload_len;
	u32 trailer_len = 0;
	size_t min_len;
	u8 eid;
	bool trailer_present;

	hdr = (struct ath10k_htc_hdr *)skb->data;
	skb_pull(skb, sizeof(*hdr));

	eid = hdr->eid;

	if (eid >= ATH10K_HTC_EP_COUNT) {
		ath10k_warn(ar, "HTC Rx: invalid eid %d\n", eid);
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad header", "",
				hdr, sizeof(*hdr));
		goto out;
	}

	ep = &htc->endpoint[eid];

	payload_len = __le16_to_cpu(hdr->len);

	if (payload_len + sizeof(*hdr) > ATH10K_HTC_MAX_LEN) {
		ath10k_warn(ar, "HTC rx frame too long, len: %zu\n",
			    payload_len + sizeof(*hdr));
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad rx pkt len", "",
				hdr, sizeof(*hdr));
		goto out;
	}

	if (skb->len < payload_len) {
		ath10k_dbg(ar, ATH10K_DBG_HTC,
			   "HTC Rx: insufficient length, got %d, expected %d\n",
			   skb->len, payload_len);
		ath10k_dbg_dump(ar, ATH10K_DBG_HTC, "htc bad rx pkt len",
				"", hdr, sizeof(*hdr));
		goto out;
	}

	/* get flags to check for trailer */
	trailer_present = hdr->flags & ATH10K_HTC_FLAG_TRAILER_PRESENT;
	if (trailer_present) {
		u8 *trailer;

		trailer_len = hdr->trailer_len;
		min_len = sizeof(struct ath10k_ath10k_htc_record_hdr);

		if ((trailer_len < min_len) ||
		    (trailer_len > payload_len)) {
			ath10k_warn(ar, "Invalid trailer length: %d\n",
				    trailer_len);
			goto out;
		}

		trailer = (u8 *)hdr;
		trailer += sizeof(*hdr);
		trailer += payload_len;
		trailer -= trailer_len;
		status = ath10k_htc_process_trailer(htc, trailer,
						    trailer_len, hdr->eid,
						    NULL, NULL);
		if (status)
			goto out;

		skb_trim(skb, skb->len - trailer_len);
	}

	if (((int)payload_len - (int)trailer_len) <= 0)
		/* zero length packet with trailer data, just drop these */
		goto out;

	ath10k_dbg(ar, ATH10K_DBG_HTC, "htc rx completion ep %d skb %pK\n",
		   eid, skb);
	ep->ep_ops.ep_rx_complete(ar, skb);

	/* skb is now owned by the rx completion handler */
	skb = NULL;
out:
	kfree_skb(skb);
}