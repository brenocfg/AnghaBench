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
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;
struct intel_guc_ct {int /*<<< orphan*/  worker; int /*<<< orphan*/  incoming_requests; int /*<<< orphan*/  pending_requests; int /*<<< orphan*/  lock; TYPE_1__ host_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTB_OWNER_HOST ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_incoming_request_worker_func ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void intel_guc_ct_init_early(struct intel_guc_ct *ct)
{
	/* we're using static channel owners */
	ct->host_channel.owner = CTB_OWNER_HOST;

	spin_lock_init(&ct->lock);
	INIT_LIST_HEAD(&ct->pending_requests);
	INIT_LIST_HEAD(&ct->incoming_requests);
	INIT_WORK(&ct->worker, ct_incoming_request_worker_func);
}