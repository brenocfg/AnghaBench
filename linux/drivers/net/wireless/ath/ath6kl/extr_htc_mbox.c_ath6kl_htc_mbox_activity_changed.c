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
struct htc_target {int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  cred_dist_list; int /*<<< orphan*/  credit_info; struct htc_endpoint* endpoint; } ;
struct TYPE_2__ {int dist_flags; int /*<<< orphan*/  txq_depth; } ;
struct htc_endpoint {scalar_t__ svc_id; int /*<<< orphan*/  txq; TYPE_1__ cred_dist; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 int /*<<< orphan*/  HTC_CREDIT_DIST_ACTIVITY_CHANGE ; 
 int HTC_EP_ACTIVE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_credit_distribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_queue_depth (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htc_chk_ep_txq (struct htc_target*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_htc_mbox_activity_changed(struct htc_target *target,
					     enum htc_endpoint_id eid,
					     bool active)
{
	struct htc_endpoint *endpoint = &target->endpoint[eid];
	bool dist = false;

	if (endpoint->svc_id == 0) {
		WARN_ON(1);
		return;
	}

	spin_lock_bh(&target->tx_lock);

	if (active) {
		if (!(endpoint->cred_dist.dist_flags & HTC_EP_ACTIVE)) {
			endpoint->cred_dist.dist_flags |= HTC_EP_ACTIVE;
			dist = true;
		}
	} else {
		if (endpoint->cred_dist.dist_flags & HTC_EP_ACTIVE) {
			endpoint->cred_dist.dist_flags &= ~HTC_EP_ACTIVE;
			dist = true;
		}
	}

	if (dist) {
		endpoint->cred_dist.txq_depth =
			get_queue_depth(&endpoint->txq);

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx activity ctxt 0x%p dist 0x%p\n",
			   target->credit_info, &target->cred_dist_list);

		ath6kl_credit_distribute(target->credit_info,
					 &target->cred_dist_list,
					 HTC_CREDIT_DIST_ACTIVITY_CHANGE);
	}

	spin_unlock_bh(&target->tx_lock);

	if (dist && !active)
		htc_chk_ep_txq(target);
}