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
struct mddev {scalar_t__ recovery_cp; scalar_t__ reshape_position; int /*<<< orphan*/  flags; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {scalar_t__ slot_number; int /*<<< orphan*/  lockspace; int /*<<< orphan*/  bitmap_lockres; int /*<<< orphan*/  resync_lockres; int /*<<< orphan*/  no_new_dev_lockres; int /*<<< orphan*/  ack_lockres; int /*<<< orphan*/  token_lockres; int /*<<< orphan*/  message_lockres; int /*<<< orphan*/  recv_thread; int /*<<< orphan*/  recovery_thread; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_CLOSING ; 
 int /*<<< orphan*/  MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct md_cluster_info*) ; 
 int /*<<< orphan*/  lockres_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resync_bitmap (struct mddev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_all_bitmaps (struct mddev*) ; 

__attribute__((used)) static int leave(struct mddev *mddev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;

	if (!cinfo)
		return 0;

	/*
	 * BITMAP_NEEDS_SYNC message should be sent when node
	 * is leaving the cluster with dirty bitmap, also we
	 * can only deliver it when dlm connection is available.
	 *
	 * Also, we should send BITMAP_NEEDS_SYNC message in
	 * case reshaping is interrupted.
	 */
	if ((cinfo->slot_number > 0 && mddev->recovery_cp != MaxSector) ||
	    (mddev->reshape_position != MaxSector &&
	     test_bit(MD_CLOSING, &mddev->flags)))
		resync_bitmap(mddev);

	set_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state);
	md_unregister_thread(&cinfo->recovery_thread);
	md_unregister_thread(&cinfo->recv_thread);
	lockres_free(cinfo->message_lockres);
	lockres_free(cinfo->token_lockres);
	lockres_free(cinfo->ack_lockres);
	lockres_free(cinfo->no_new_dev_lockres);
	lockres_free(cinfo->resync_lockres);
	lockres_free(cinfo->bitmap_lockres);
	unlock_all_bitmaps(mddev);
	dlm_release_lockspace(cinfo->lockspace, 2);
	kfree(cinfo);
	return 0;
}