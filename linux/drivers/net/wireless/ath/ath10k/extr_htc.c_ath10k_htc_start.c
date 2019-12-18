#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {int /*<<< orphan*/  max_msgs_per_bundled_recv; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  message_id; } ;
struct ath10k_htc_msg {TYPE_3__ setup_complete_ext; TYPE_1__ hdr; } ;
struct ath10k_htc {int /*<<< orphan*/  max_msgs_per_htc_bundle; struct ath10k* ar; } ;
struct TYPE_5__ {scalar_t__ bus; } ;
struct ath10k {TYPE_2__ hif; } ;

/* Variables and functions */
 scalar_t__ ATH10K_BUS_SDIO ; 
 int /*<<< orphan*/  ATH10K_DBG_HTC ; 
 int /*<<< orphan*/  ATH10K_HTC_EP_0 ; 
 int /*<<< orphan*/  ATH10K_HTC_MSG_SETUP_COMPLETE_EX_ID ; 
 int /*<<< orphan*/  ATH10K_HTC_SETUP_COMPLETE_FLAGS_RX_BNDL_EN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  __cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 struct sk_buff* ath10k_htc_build_tx_ctrl_skb (struct ath10k*) ; 
 int ath10k_htc_pktlog_connect (struct ath10k*) ; 
 scalar_t__ ath10k_htc_pktlog_svc_supported (struct ath10k*) ; 
 int ath10k_htc_send (struct ath10k_htc*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

int ath10k_htc_start(struct ath10k_htc *htc)
{
	struct ath10k *ar = htc->ar;
	struct sk_buff *skb;
	int status = 0;
	struct ath10k_htc_msg *msg;

	skb = ath10k_htc_build_tx_ctrl_skb(htc->ar);
	if (!skb)
		return -ENOMEM;

	skb_put(skb, sizeof(msg->hdr) + sizeof(msg->setup_complete_ext));
	memset(skb->data, 0, skb->len);

	msg = (struct ath10k_htc_msg *)skb->data;
	msg->hdr.message_id =
		__cpu_to_le16(ATH10K_HTC_MSG_SETUP_COMPLETE_EX_ID);

	if (ar->hif.bus == ATH10K_BUS_SDIO) {
		/* Extra setup params used by SDIO */
		msg->setup_complete_ext.flags =
			__cpu_to_le32(ATH10K_HTC_SETUP_COMPLETE_FLAGS_RX_BNDL_EN);
		msg->setup_complete_ext.max_msgs_per_bundled_recv =
			htc->max_msgs_per_htc_bundle;
	}
	ath10k_dbg(ar, ATH10K_DBG_HTC, "HTC is using TX credit flow control\n");

	status = ath10k_htc_send(htc, ATH10K_HTC_EP_0, skb);
	if (status) {
		kfree_skb(skb);
		return status;
	}

	if (ath10k_htc_pktlog_svc_supported(ar)) {
		status = ath10k_htc_pktlog_connect(ar);
		if (status) {
			ath10k_err(ar, "failed to connect to pktlog: %d\n", status);
			return status;
		}
	}

	return 0;
}