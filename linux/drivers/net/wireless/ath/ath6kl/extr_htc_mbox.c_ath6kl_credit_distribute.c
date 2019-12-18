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
struct list_head {int dummy; } ;
struct ath6kl_htc_credit_info {scalar_t__ cur_free_credits; scalar_t__ total_avail_credits; } ;
typedef  enum htc_credit_dist_reason { ____Placeholder_htc_credit_dist_reason } htc_credit_dist_reason ;

/* Variables and functions */
#define  HTC_CREDIT_DIST_ACTIVITY_CHANGE 129 
#define  HTC_CREDIT_DIST_SEND_COMPLETE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ath6kl_credit_redistribute (struct ath6kl_htc_credit_info*,struct list_head*) ; 
 int /*<<< orphan*/  ath6kl_credit_update (struct ath6kl_htc_credit_info*,struct list_head*) ; 

__attribute__((used)) static void ath6kl_credit_distribute(struct ath6kl_htc_credit_info *cred_info,
				     struct list_head *ep_dist_list,
			      enum htc_credit_dist_reason reason)
{
	switch (reason) {
	case HTC_CREDIT_DIST_SEND_COMPLETE:
		ath6kl_credit_update(cred_info, ep_dist_list);
		break;
	case HTC_CREDIT_DIST_ACTIVITY_CHANGE:
		ath6kl_credit_redistribute(cred_info, ep_dist_list);
		break;
	default:
		break;
	}

	WARN_ON(cred_info->cur_free_credits > cred_info->total_avail_credits);
	WARN_ON(cred_info->cur_free_credits < 0);
}