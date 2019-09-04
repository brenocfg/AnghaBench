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
struct md_cluster_info {int /*<<< orphan*/  state; int /*<<< orphan*/  recv_thread; } ;
struct dlm_lock_resource {TYPE_1__* mddev; } ;
struct TYPE_2__ {struct md_cluster_info* cluster_info; } ;

/* Variables and functions */
 int DLM_LOCK_EX ; 
 int /*<<< orphan*/  MD_CLUSTER_ALREADY_IN_CLUSTER ; 
 int /*<<< orphan*/  MD_CLUSTER_PENDING_RECV_EVENT ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ack_bast(void *arg, int mode)
{
	struct dlm_lock_resource *res = arg;
	struct md_cluster_info *cinfo = res->mddev->cluster_info;

	if (mode == DLM_LOCK_EX) {
		if (test_bit(MD_CLUSTER_ALREADY_IN_CLUSTER, &cinfo->state))
			md_wakeup_thread(cinfo->recv_thread);
		else
			set_bit(MD_CLUSTER_PENDING_RECV_EVENT, &cinfo->state);
	}
}