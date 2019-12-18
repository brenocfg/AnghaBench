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
struct htc_target {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  cred_dist_list; int /*<<< orphan*/  credit_info; } ;
struct TYPE_4__ {scalar_t__ cred_used; } ;
struct TYPE_5__ {TYPE_1__ tx; } ;
struct htc_packet {TYPE_2__ info; int /*<<< orphan*/  act_len; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  status; int /*<<< orphan*/  buf; int /*<<< orphan*/ * completion; } ;
struct TYPE_6__ {int /*<<< orphan*/  txq_depth; int /*<<< orphan*/  cred_to_dist; } ;
struct htc_endpoint {int /*<<< orphan*/  txq; TYPE_3__ cred_dist; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  HTC_CREDIT_DIST_SEND_COMPLETE ; 
 scalar_t__ HTC_HDR_LENGTH ; 
 int /*<<< orphan*/  ath6kl_credit_distribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath6kl_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htc_tx_comp_update(struct htc_target *target,
			       struct htc_endpoint *endpoint,
			       struct htc_packet *packet)
{
	packet->completion = NULL;
	packet->buf += HTC_HDR_LENGTH;

	if (!packet->status)
		return;

	ath6kl_err("req failed (status:%d, ep:%d, len:%d creds:%d)\n",
		   packet->status, packet->endpoint, packet->act_len,
		   packet->info.tx.cred_used);

	/* on failure to submit, reclaim credits for this packet */
	spin_lock_bh(&target->tx_lock);
	endpoint->cred_dist.cred_to_dist +=
				packet->info.tx.cred_used;
	endpoint->cred_dist.txq_depth = get_queue_depth(&endpoint->txq);

	ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx ctxt 0x%p dist 0x%p\n",
		   target->credit_info, &target->cred_dist_list);

	ath6kl_credit_distribute(target->credit_info,
				 &target->cred_dist_list,
				 HTC_CREDIT_DIST_SEND_COMPLETE);

	spin_unlock_bh(&target->tx_lock);
}