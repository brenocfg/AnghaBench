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
struct TYPE_2__ {int /*<<< orphan*/  (* ep_tx_credits ) (struct ath10k*) ;} ;
struct ath10k_htc_ep {TYPE_1__ ep_ops; int /*<<< orphan*/  tx_credits; } ;
struct ath10k_htc_credit_report {size_t eid; scalar_t__ credits; } ;
struct ath10k_htc {int /*<<< orphan*/  tx_lock; struct ath10k* ar; struct ath10k_htc_ep* endpoint; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_HTC ; 
 size_t ATH10K_HTC_EP_COUNT ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ath10k*) ; 

__attribute__((used)) static void
ath10k_htc_process_credit_report(struct ath10k_htc *htc,
				 const struct ath10k_htc_credit_report *report,
				 int len,
				 enum ath10k_htc_ep_id eid)
{
	struct ath10k *ar = htc->ar;
	struct ath10k_htc_ep *ep;
	int i, n_reports;

	if (len % sizeof(*report))
		ath10k_warn(ar, "Uneven credit report len %d", len);

	n_reports = len / sizeof(*report);

	spin_lock_bh(&htc->tx_lock);
	for (i = 0; i < n_reports; i++, report++) {
		if (report->eid >= ATH10K_HTC_EP_COUNT)
			break;

		ep = &htc->endpoint[report->eid];
		ep->tx_credits += report->credits;

		ath10k_dbg(ar, ATH10K_DBG_HTC, "htc ep %d got %d credits (total %d)\n",
			   report->eid, report->credits, ep->tx_credits);

		if (ep->ep_ops.ep_tx_credits) {
			spin_unlock_bh(&htc->tx_lock);
			ep->ep_ops.ep_tx_credits(htc->ar);
			spin_lock_bh(&htc->tx_lock);
		}
	}
	spin_unlock_bh(&htc->tx_lock);
}