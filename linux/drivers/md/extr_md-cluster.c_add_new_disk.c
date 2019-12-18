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
struct mdp_superblock_1 {char* device_uuid; } ;
struct mddev {struct md_cluster_info* cluster_info; } ;
struct md_rdev {int /*<<< orphan*/  desc_nr; int /*<<< orphan*/  sb_page; } ;
struct md_cluster_info {int /*<<< orphan*/  wait; int /*<<< orphan*/  state; TYPE_1__* no_new_dev_lockres; } ;
struct cluster_msg {void* raid_slot; int /*<<< orphan*/  uuid; void* type; } ;
typedef  int /*<<< orphan*/  cmsg ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_NOQUEUE ; 
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  MD_CLUSTER_SEND_LOCKED_ALREADY ; 
 int /*<<< orphan*/  NEWDISK ; 
 int __sendmsg (struct md_cluster_info*,struct cluster_msg*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int dlm_lock_sync (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_comm (struct md_cluster_info*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct cluster_msg*,int /*<<< orphan*/ ,int) ; 
 struct mdp_superblock_1* page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_comm (struct md_cluster_info*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_new_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct md_cluster_info *cinfo = mddev->cluster_info;
	struct cluster_msg cmsg;
	int ret = 0;
	struct mdp_superblock_1 *sb = page_address(rdev->sb_page);
	char *uuid = sb->device_uuid;

	memset(&cmsg, 0, sizeof(cmsg));
	cmsg.type = cpu_to_le32(NEWDISK);
	memcpy(cmsg.uuid, uuid, 16);
	cmsg.raid_slot = cpu_to_le32(rdev->desc_nr);
	lock_comm(cinfo, 1);
	ret = __sendmsg(cinfo, &cmsg);
	if (ret) {
		unlock_comm(cinfo);
		return ret;
	}
	cinfo->no_new_dev_lockres->flags |= DLM_LKF_NOQUEUE;
	ret = dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_EX);
	cinfo->no_new_dev_lockres->flags &= ~DLM_LKF_NOQUEUE;
	/* Some node does not "see" the device */
	if (ret == -EAGAIN)
		ret = -ENOENT;
	if (ret)
		unlock_comm(cinfo);
	else {
		dlm_lock_sync(cinfo->no_new_dev_lockres, DLM_LOCK_CR);
		/* Since MD_CHANGE_DEVS will be set in add_bound_rdev which
		 * will run soon after add_new_disk, the below path will be
		 * invoked:
		 *   md_wakeup_thread(mddev->thread)
		 *	-> conf->thread (raid1d)
		 *	-> md_check_recovery -> md_update_sb
		 *	-> metadata_update_start/finish
		 * MD_CLUSTER_SEND_LOCKED_ALREADY will be cleared eventually.
		 *
		 * For other failure cases, metadata_update_cancel and
		 * add_new_disk_cancel also clear below bit as well.
		 * */
		set_bit(MD_CLUSTER_SEND_LOCKED_ALREADY, &cinfo->state);
		wake_up(&cinfo->wait);
	}
	return ret;
}