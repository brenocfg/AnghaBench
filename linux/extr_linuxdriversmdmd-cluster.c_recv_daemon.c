#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct md_thread {TYPE_2__* mddev; } ;
struct md_cluster_info {int /*<<< orphan*/  recv_mutex; struct dlm_lock_resource* message_lockres; struct dlm_lock_resource* ack_lockres; } ;
struct TYPE_3__ {int /*<<< orphan*/  sb_lvbptr; } ;
struct dlm_lock_resource {TYPE_1__ lksb; } ;
struct cluster_msg {int dummy; } ;
struct TYPE_4__ {struct md_cluster_info* cluster_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  DLM_LOCK_PR ; 
 int dlm_lock_sync (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int dlm_unlock_sync (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  memcpy (struct cluster_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int process_recvd_msg (TYPE_2__*,struct cluster_msg*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void recv_daemon(struct md_thread *thread)
{
	struct md_cluster_info *cinfo = thread->mddev->cluster_info;
	struct dlm_lock_resource *ack_lockres = cinfo->ack_lockres;
	struct dlm_lock_resource *message_lockres = cinfo->message_lockres;
	struct cluster_msg msg;
	int ret;

	mutex_lock(&cinfo->recv_mutex);
	/*get CR on Message*/
	if (dlm_lock_sync(message_lockres, DLM_LOCK_CR)) {
		pr_err("md/raid1:failed to get CR on MESSAGE\n");
		mutex_unlock(&cinfo->recv_mutex);
		return;
	}

	/* read lvb and wake up thread to process this message_lockres */
	memcpy(&msg, message_lockres->lksb.sb_lvbptr, sizeof(struct cluster_msg));
	ret = process_recvd_msg(thread->mddev, &msg);
	if (ret)
		goto out;

	/*release CR on ack_lockres*/
	ret = dlm_unlock_sync(ack_lockres);
	if (unlikely(ret != 0))
		pr_info("unlock ack failed return %d\n", ret);
	/*up-convert to PR on message_lockres*/
	ret = dlm_lock_sync(message_lockres, DLM_LOCK_PR);
	if (unlikely(ret != 0))
		pr_info("lock PR on msg failed return %d\n", ret);
	/*get CR on ack_lockres again*/
	ret = dlm_lock_sync(ack_lockres, DLM_LOCK_CR);
	if (unlikely(ret != 0))
		pr_info("lock CR on ack failed return %d\n", ret);
out:
	/*release CR on message_lockres*/
	ret = dlm_unlock_sync(message_lockres);
	if (unlikely(ret != 0))
		pr_info("unlock msg failed return %d\n", ret);
	mutex_unlock(&cinfo->recv_mutex);
}