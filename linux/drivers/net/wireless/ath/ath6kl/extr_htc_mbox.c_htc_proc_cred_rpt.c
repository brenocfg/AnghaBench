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
struct htc_target {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  cred_dist_list; int /*<<< orphan*/  credit_info; struct htc_endpoint* endpoint; } ;
struct TYPE_4__ {int /*<<< orphan*/  txq_depth; int /*<<< orphan*/  cred_to_dist; int /*<<< orphan*/  credits; } ;
struct TYPE_3__ {int tx_cred_rpt; int cred_rpt_from_rx; int cred_rpt_ep0; int cred_rpt_from_other; int /*<<< orphan*/  cred_from_other; int /*<<< orphan*/  cred_from_ep0; int /*<<< orphan*/  cred_from_rx; int /*<<< orphan*/  cred_retnd; } ;
struct htc_endpoint {int /*<<< orphan*/  txq; TYPE_2__ cred_dist; TYPE_1__ ep_st; } ;
struct htc_credit_report {size_t eid; scalar_t__ credits; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_CREDIT ; 
 int ENDPOINT_0 ; 
 size_t ENDPOINT_MAX ; 
 int /*<<< orphan*/  HTC_CREDIT_DIST_SEND_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_credit_distribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htc_chk_ep_txq (struct htc_target*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htc_proc_cred_rpt(struct htc_target *target,
			      struct htc_credit_report *rpt,
			      int n_entries,
			      enum htc_endpoint_id from_ep)
{
	struct htc_endpoint *endpoint;
	int tot_credits = 0, i;
	bool dist = false;

	spin_lock_bh(&target->tx_lock);

	for (i = 0; i < n_entries; i++, rpt++) {
		if (rpt->eid >= ENDPOINT_MAX) {
			WARN_ON(1);
			spin_unlock_bh(&target->tx_lock);
			return;
		}

		endpoint = &target->endpoint[rpt->eid];

		ath6kl_dbg(ATH6KL_DBG_CREDIT,
			   "credit report ep %d credits %d\n",
			   rpt->eid, rpt->credits);

		endpoint->ep_st.tx_cred_rpt += 1;
		endpoint->ep_st.cred_retnd += rpt->credits;

		if (from_ep == rpt->eid) {
			/*
			 * This credit report arrived on the same endpoint
			 * indicating it arrived in an RX packet.
			 */
			endpoint->ep_st.cred_from_rx += rpt->credits;
			endpoint->ep_st.cred_rpt_from_rx += 1;
		} else if (from_ep == ENDPOINT_0) {
			/* credit arrived on endpoint 0 as a NULL message */
			endpoint->ep_st.cred_from_ep0 += rpt->credits;
			endpoint->ep_st.cred_rpt_ep0 += 1;
		} else {
			endpoint->ep_st.cred_from_other += rpt->credits;
			endpoint->ep_st.cred_rpt_from_other += 1;
		}

		if (rpt->eid == ENDPOINT_0)
			/* always give endpoint 0 credits back */
			endpoint->cred_dist.credits += rpt->credits;
		else {
			endpoint->cred_dist.cred_to_dist += rpt->credits;
			dist = true;
		}

		/*
		 * Refresh tx depth for distribution function that will
		 * recover these credits NOTE: this is only valid when
		 * there are credits to recover!
		 */
		endpoint->cred_dist.txq_depth =
			get_queue_depth(&endpoint->txq);

		tot_credits += rpt->credits;
	}

	if (dist) {
		/*
		 * This was a credit return based on a completed send
		 * operations note, this is done with the lock held
		 */
		ath6kl_credit_distribute(target->credit_info,
					 &target->cred_dist_list,
					 HTC_CREDIT_DIST_SEND_COMPLETE);
	}

	spin_unlock_bh(&target->tx_lock);

	if (tot_credits)
		htc_chk_ep_txq(target);
}