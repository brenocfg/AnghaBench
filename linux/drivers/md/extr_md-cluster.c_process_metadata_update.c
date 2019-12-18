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
struct mddev {int /*<<< orphan*/  good_device_nr; TYPE_1__* thread; struct md_cluster_info* cluster_info; } ;
struct md_cluster_info {int /*<<< orphan*/  state; int /*<<< orphan*/  no_new_dev_lockres; } ;
struct cluster_msg {int /*<<< orphan*/  raid_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  wqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD ; 
 int /*<<< orphan*/  dlm_lock_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_reload_sb (struct mddev*,int /*<<< orphan*/ ) ; 
 int mddev_trylock (struct mddev*) ; 
 int /*<<< orphan*/  mddev_unlock (struct mddev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void process_metadata_update(struct mddev *mddev, struct cluster_msg *msg)
{
	int got_lock = 0;
	struct md_cluster_info *cinfo = mddev->cluster_info;
	mddev->good_device_nr = le32_to_cpu(msg->raid_slot);

	dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_CR);
	wait_event(mddev->thread->wqueue,
		   (got_lock = mddev_trylock(mddev)) ||
		    test_bit(MD_CLUSTER_HOLDING_MUTEX_FOR_RECVD, &cinfo->state));
	md_reload_sb(mddev, mddev->good_device_nr);
	if (got_lock)
		mddev_unlock(mddev);
}