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
struct tx_mgmt_hdr {int cookie; } ;
struct tx_frame_hdr {int cookie; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath_common {int dummy; } ;
struct ath9k_htc_tx_ctl {scalar_t__ epid; } ;
struct ath9k_htc_priv {scalar_t__ mgmt_ep; scalar_t__ data_bk_ep; scalar_t__ data_be_ep; scalar_t__ data_vi_ep; scalar_t__ data_vo_ep; scalar_t__ cab_ep; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ath9k_htc_tx_ctl* HTC_SKB_CB (struct sk_buff*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,scalar_t__) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static inline int strip_drv_header(struct ath9k_htc_priv *priv,
				   struct sk_buff *skb)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath9k_htc_tx_ctl *tx_ctl;
	int slot;

	tx_ctl = HTC_SKB_CB(skb);

	if (tx_ctl->epid == priv->mgmt_ep) {
		struct tx_mgmt_hdr *tx_mhdr =
			(struct tx_mgmt_hdr *)skb->data;
		slot = tx_mhdr->cookie;
		skb_pull(skb, sizeof(struct tx_mgmt_hdr));
	} else if ((tx_ctl->epid == priv->data_bk_ep) ||
		   (tx_ctl->epid == priv->data_be_ep) ||
		   (tx_ctl->epid == priv->data_vi_ep) ||
		   (tx_ctl->epid == priv->data_vo_ep) ||
		   (tx_ctl->epid == priv->cab_ep)) {
		struct tx_frame_hdr *tx_fhdr =
			(struct tx_frame_hdr *)skb->data;
		slot = tx_fhdr->cookie;
		skb_pull(skb, sizeof(struct tx_frame_hdr));
	} else {
		ath_err(common, "Unsupported EPID: %d\n", tx_ctl->epid);
		slot = -EINVAL;
	}

	return slot;
}