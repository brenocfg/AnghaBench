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
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  recv_thread; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CLUSTER_ALREADY_IN_CLUSTER ; 
 int /*<<< orphan*/  MD_CLUSTER_PENDING_RECV_EVENT ; 
 scalar_t__ gather_all_resync_info (struct mddev*,int) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void load_bitmaps(struct mddev *mddev, int total_slots)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;

	/* load all the node's bitmap info for resync */
	if (gather_all_resync_info(mddev, total_slots))
		pr_err("md-cluster: failed to gather all resyn infos\n");
	set_bit(MD_CLUSTER_ALREADY_IN_CLUSTER, &cinfo->state);
	/* wake up recv thread in case something need to be handled */
	if (test_and_clear_bit(MD_CLUSTER_PENDING_RECV_EVENT, &cinfo->state))
		md_wakeup_thread(cinfo->recv_thread);
}