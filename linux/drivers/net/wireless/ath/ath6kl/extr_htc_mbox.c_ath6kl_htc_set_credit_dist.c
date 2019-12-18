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
typedef  scalar_t__ u16 ;
struct htc_target {int /*<<< orphan*/  cred_dist_list; struct htc_endpoint* endpoint; struct ath6kl_htc_credit_info* credit_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct htc_endpoint {scalar_t__ svc_id; TYPE_1__ cred_dist; } ;
struct ath6kl_htc_credit_info {int dummy; } ;

/* Variables and functions */
 size_t ENDPOINT_0 ; 
 int ENDPOINT_1 ; 
 int ENDPOINT_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_htc_set_credit_dist(struct htc_target *target,
				struct ath6kl_htc_credit_info *credit_info,
				u16 srvc_pri_order[], int list_len)
{
	struct htc_endpoint *endpoint;
	int i, ep;

	target->credit_info = credit_info;

	list_add_tail(&target->endpoint[ENDPOINT_0].cred_dist.list,
		      &target->cred_dist_list);

	for (i = 0; i < list_len; i++) {
		for (ep = ENDPOINT_1; ep < ENDPOINT_MAX; ep++) {
			endpoint = &target->endpoint[ep];
			if (endpoint->svc_id == srvc_pri_order[i]) {
				list_add_tail(&endpoint->cred_dist.list,
					      &target->cred_dist_list);
				break;
			}
		}
		if (ep >= ENDPOINT_MAX) {
			WARN_ON(1);
			return;
		}
	}
}