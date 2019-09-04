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
struct mddev {int /*<<< orphan*/  thread; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  state; TYPE_1__* token_lockres; int /*<<< orphan*/  wait; } ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_EX ; 
 int /*<<< orphan*/  MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD ; 
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCK ; 
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCKED_ALREADY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int lock_token (struct md_cluster_info*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int metadata_update_start(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	int ret;

	/*
	 * metadata_update_start is always called with the protection of
	 * reconfig_mutex, so set WAITING_FOR_TOKEN here.
	 */
	ret = test_and_set_bit_lock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD,
				    &cinfo->state);
	WARN_ON_ONCE(ret);
	md_wakeup_thread(mddev->thread);

	wait_event(cinfo->wait,
		   !test_and_set_bit(MD_CLUSTER_SEND_LOCK, &cinfo->state) ||
		   test_and_clear_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state));

	/* If token is already locked, return 0 */
	if (cinfo->token_lockres->mode == DLM_LOCK_EX) {
		clear_bit_unlock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
		return 0;
	}

	ret = lock_token(cinfo, 1);
	clear_bit_unlock(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	return ret;
}