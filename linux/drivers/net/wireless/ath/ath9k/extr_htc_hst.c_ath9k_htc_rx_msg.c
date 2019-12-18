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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;
struct htc_target {struct htc_endpoint* endpoint; } ;
struct htc_frame_hdr {int endpoint_id; int flags; scalar_t__* control; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; int /*<<< orphan*/  (* rx ) (int /*<<< orphan*/ ,struct sk_buff*,int) ;} ;
struct htc_endpoint {TYPE_1__ ep_callbacks; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int ENDPOINT0 ; 
 int ENDPOINT_MAX ; 
 int HTC_FLAGS_RECV_TRAILER ; 
#define  HTC_MSG_CONNECT_SERVICE_RESPONSE_ID 129 
#define  HTC_MSG_READY_ID 128 
 scalar_t__ USB_REG_IN_PIPE ; 
 int /*<<< orphan*/  ath9k_htc_fw_panic_report (struct htc_target*,struct sk_buff*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  htc_process_conn_rsp (struct htc_target*,struct htc_frame_hdr*) ; 
 int /*<<< orphan*/  htc_process_target_rdy (struct htc_target*,struct htc_frame_hdr*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct sk_buff*,int) ; 

void ath9k_htc_rx_msg(struct htc_target *htc_handle,
		      struct sk_buff *skb, u32 len, u8 pipe_id)
{
	struct htc_frame_hdr *htc_hdr;
	enum htc_endpoint_id epid;
	struct htc_endpoint *endpoint;
	__be16 *msg_id;

	if (!htc_handle || !skb)
		return;

	htc_hdr = (struct htc_frame_hdr *) skb->data;
	epid = htc_hdr->endpoint_id;

	if (epid == 0x99) {
		ath9k_htc_fw_panic_report(htc_handle, skb);
		kfree_skb(skb);
		return;
	}

	if (epid < 0 || epid >= ENDPOINT_MAX) {
		if (pipe_id != USB_REG_IN_PIPE)
			dev_kfree_skb_any(skb);
		else
			kfree_skb(skb);
		return;
	}

	if (epid == ENDPOINT0) {

		/* Handle trailer */
		if (htc_hdr->flags & HTC_FLAGS_RECV_TRAILER) {
			if (be32_to_cpu(*(__be32 *) skb->data) == 0x00C60000)
				/* Move past the Watchdog pattern */
				htc_hdr = (struct htc_frame_hdr *)(skb->data + 4);
		}

		/* Get the message ID */
		msg_id = (__be16 *) ((void *) htc_hdr +
				     sizeof(struct htc_frame_hdr));

		/* Now process HTC messages */
		switch (be16_to_cpu(*msg_id)) {
		case HTC_MSG_READY_ID:
			htc_process_target_rdy(htc_handle, htc_hdr);
			break;
		case HTC_MSG_CONNECT_SERVICE_RESPONSE_ID:
			htc_process_conn_rsp(htc_handle, htc_hdr);
			break;
		default:
			break;
		}

		kfree_skb(skb);

	} else {
		if (htc_hdr->flags & HTC_FLAGS_RECV_TRAILER)
			skb_trim(skb, len - htc_hdr->control[0]);

		skb_pull(skb, sizeof(struct htc_frame_hdr));

		endpoint = &htc_handle->endpoint[epid];
		if (endpoint->ep_callbacks.rx)
			endpoint->ep_callbacks.rx(endpoint->ep_callbacks.priv,
						  skb, epid);
	}
}