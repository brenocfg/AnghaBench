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
struct htc_target {int /*<<< orphan*/ * endpoint; } ;
struct htc_packet {scalar_t__ endpoint; scalar_t__ act_len; scalar_t__ buf; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  ECANCELED ; 
 scalar_t__ ENDPOINT_0 ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_dbg_dump (int /*<<< orphan*/ ,char*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ath6kl_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  htc_reclaim_rxbuf (struct htc_target*,struct htc_packet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reclaim_rx_ctrl_buf (struct htc_target*,struct htc_packet*) ; 

__attribute__((used)) static void htc_ctrl_rx(struct htc_target *context, struct htc_packet *packets)
{
	if (packets->endpoint != ENDPOINT_0) {
		WARN_ON(1);
		return;
	}

	if (packets->status == -ECANCELED) {
		reclaim_rx_ctrl_buf(context, packets);
		return;
	}

	if (packets->act_len > 0) {
		ath6kl_err("htc_ctrl_rx, got message with len:%zu\n",
			   packets->act_len + HTC_HDR_LENGTH);

		ath6kl_dbg_dump(ATH6KL_DBG_HTC,
				"htc rx unexpected endpoint 0 message", "",
				packets->buf - HTC_HDR_LENGTH,
				packets->act_len + HTC_HDR_LENGTH);
	}

	htc_reclaim_rxbuf(context, packets, &context->endpoint[0]);
}