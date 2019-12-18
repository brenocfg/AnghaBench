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
typedef  int /*<<< orphan*/  u8 ;
struct htc_target {unsigned int tgt_cred_sz; int /*<<< orphan*/  credit_info; } ;
struct TYPE_3__ {int cred_cosumd; int cred_low_indicate; } ;
struct TYPE_4__ {int credits; int seek_cred; int cred_per_msg; } ;
struct htc_endpoint {TYPE_1__ ep_st; TYPE_2__ cred_dist; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_CREDIT ; 
 int DIV_ROUND_UP (unsigned int,unsigned int) ; 
 int EINVAL ; 
 int ENDPOINT_0 ; 
 int /*<<< orphan*/  HTC_FLAGS_NEED_CREDIT_UPDATE ; 
 int /*<<< orphan*/  ath6kl_credit_seek (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int htc_check_credits(struct htc_target *target,
			     struct htc_endpoint *ep, u8 *flags,
			     enum htc_endpoint_id eid, unsigned int len,
			     int *req_cred)
{
	*req_cred = (len > target->tgt_cred_sz) ?
		     DIV_ROUND_UP(len, target->tgt_cred_sz) : 1;

	ath6kl_dbg(ATH6KL_DBG_CREDIT, "credit check need %d got %d\n",
		   *req_cred, ep->cred_dist.credits);

	if (ep->cred_dist.credits < *req_cred) {
		if (eid == ENDPOINT_0)
			return -EINVAL;

		/* Seek more credits */
		ep->cred_dist.seek_cred = *req_cred - ep->cred_dist.credits;

		ath6kl_credit_seek(target->credit_info, &ep->cred_dist);

		ep->cred_dist.seek_cred = 0;

		if (ep->cred_dist.credits < *req_cred) {
			ath6kl_dbg(ATH6KL_DBG_CREDIT,
				   "credit not found for ep %d\n",
				   eid);
			return -EINVAL;
		}
	}

	ep->cred_dist.credits -= *req_cred;
	ep->ep_st.cred_cosumd += *req_cred;

	 /* When we are getting low on credits, ask for more */
	if (ep->cred_dist.credits < ep->cred_dist.cred_per_msg) {
		ep->cred_dist.seek_cred =
		ep->cred_dist.cred_per_msg - ep->cred_dist.credits;

		ath6kl_credit_seek(target->credit_info, &ep->cred_dist);

		/* see if we were successful in getting more */
		if (ep->cred_dist.credits < ep->cred_dist.cred_per_msg) {
			/* tell the target we need credits ASAP! */
			*flags |= HTC_FLAGS_NEED_CREDIT_UPDATE;
			ep->ep_st.cred_low_indicate += 1;
			ath6kl_dbg(ATH6KL_DBG_CREDIT,
				   "credit we need credits asap\n");
		}
	}

	return 0;
}