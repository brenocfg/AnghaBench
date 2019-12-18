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
struct htc_target {int /*<<< orphan*/  cred_dist_list; struct htc_endpoint* endpoint; } ;
struct htc_endpoint {struct htc_target* target; int /*<<< orphan*/  txq; int /*<<< orphan*/  rx_bufq; int /*<<< orphan*/  ep_st; scalar_t__ max_txq_depth; scalar_t__ len_max; scalar_t__ svc_id; int /*<<< orphan*/  cred_dist; } ;

/* Variables and functions */
 int ENDPOINT_0 ; 
 int ENDPOINT_MAX ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_ep_state(struct htc_target *target)
{
	struct htc_endpoint *endpoint;
	int i;

	for (i = ENDPOINT_0; i < ENDPOINT_MAX; i++) {
		endpoint = &target->endpoint[i];
		memset(&endpoint->cred_dist, 0, sizeof(endpoint->cred_dist));
		endpoint->svc_id = 0;
		endpoint->len_max = 0;
		endpoint->max_txq_depth = 0;
		memset(&endpoint->ep_st, 0,
		       sizeof(endpoint->ep_st));
		INIT_LIST_HEAD(&endpoint->rx_bufq);
		INIT_LIST_HEAD(&endpoint->txq);
		endpoint->target = target;
	}

	/* reset distribution list */
	/* FIXME: free existing entries */
	INIT_LIST_HEAD(&target->cred_dist_list);
}