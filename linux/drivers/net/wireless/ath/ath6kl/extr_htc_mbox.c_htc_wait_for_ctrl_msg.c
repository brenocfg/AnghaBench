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
typedef  scalar_t__ u32 ;
struct htc_target {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ exp_hdr; scalar_t__ rx_flags; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct htc_packet {scalar_t__ act_len; scalar_t__ buf_len; scalar_t__ status; int /*<<< orphan*/  buf; int /*<<< orphan*/  endpoint; int /*<<< orphan*/ * completion; TYPE_2__ info; } ;
struct htc_frame_hdr {scalar_t__ eid; int /*<<< orphan*/  payld_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 scalar_t__ ENDPOINT_0 ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 int /*<<< orphan*/  HTC_TARGET_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,scalar_t__) ; 
 scalar_t__ ath6kl_hif_poll_mboxmsg_rx (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath6kl_htc_rx_packet (struct htc_target*,struct htc_packet*,scalar_t__) ; 
 scalar_t__ ath6kl_htc_rx_process_hdr (struct htc_target*,struct htc_packet*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct htc_packet* htc_get_control_buf (struct htc_target*,int) ; 
 int /*<<< orphan*/  htc_rxpkt_reset (struct htc_packet*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reclaim_rx_ctrl_buf (struct htc_target*,struct htc_packet*) ; 
 int /*<<< orphan*/  trace_ath6kl_htc_rx (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static struct htc_packet *htc_wait_for_ctrl_msg(struct htc_target *target)
{
	struct htc_packet *packet = NULL;
	struct htc_frame_hdr *htc_hdr;
	u32 look_ahead;

	if (ath6kl_hif_poll_mboxmsg_rx(target->dev, &look_ahead,
				       HTC_TARGET_RESPONSE_TIMEOUT))
		return NULL;

	ath6kl_dbg(ATH6KL_DBG_HTC,
		   "htc rx wait ctrl look_ahead 0x%X\n", look_ahead);

	htc_hdr = (struct htc_frame_hdr *)&look_ahead;

	if (htc_hdr->eid != ENDPOINT_0)
		return NULL;

	packet = htc_get_control_buf(target, false);

	if (!packet)
		return NULL;

	packet->info.rx.rx_flags = 0;
	packet->info.rx.exp_hdr = look_ahead;
	packet->act_len = le16_to_cpu(htc_hdr->payld_len) + HTC_HDR_LENGTH;

	if (packet->act_len > packet->buf_len)
		goto fail_ctrl_rx;

	/* we want synchronous operation */
	packet->completion = NULL;

	/* get the message from the device, this will block */
	if (ath6kl_htc_rx_packet(target, packet, packet->act_len))
		goto fail_ctrl_rx;

	trace_ath6kl_htc_rx(packet->status, packet->endpoint,
			    packet->buf, packet->act_len);

	/* process receive header */
	packet->status = ath6kl_htc_rx_process_hdr(target, packet, NULL, NULL);

	if (packet->status) {
		ath6kl_err("htc_wait_for_ctrl_msg, ath6kl_htc_rx_process_hdr failed (status = %d)\n",
			   packet->status);
		goto fail_ctrl_rx;
	}

	return packet;

fail_ctrl_rx:
	if (packet != NULL) {
		htc_rxpkt_reset(packet);
		reclaim_rx_ctrl_buf(target, packet);
	}

	return NULL;
}