#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct md_cluster_info {int slot_number; TYPE_2__* message_lockres; TYPE_2__* ack_lockres; } ;
struct cluster_msg {int /*<<< orphan*/  slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_lvbptr; } ;
struct TYPE_5__ {TYPE_1__ lksb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_CR ; 
 int /*<<< orphan*/  DLM_LOCK_CW ; 
 int /*<<< orphan*/  DLM_LOCK_EX ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int dlm_lock_sync (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dlm_unlock_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __sendmsg(struct md_cluster_info *cinfo, struct cluster_msg *cmsg)
{
	int error;
	int slot = cinfo->slot_number - 1;

	cmsg->slot = cpu_to_le32(slot);
	/*get EX on Message*/
	error = dlm_lock_sync(cinfo->message_lockres, DLM_LOCK_EX);
	if (error) {
		pr_err("md-cluster: failed to get EX on MESSAGE (%d)\n", error);
		goto failed_message;
	}

	memcpy(cinfo->message_lockres->lksb.sb_lvbptr, (void *)cmsg,
			sizeof(struct cluster_msg));
	/*down-convert EX to CW on Message*/
	error = dlm_lock_sync(cinfo->message_lockres, DLM_LOCK_CW);
	if (error) {
		pr_err("md-cluster: failed to convert EX to CW on MESSAGE(%d)\n",
				error);
		goto failed_ack;
	}

	/*up-convert CR to EX on Ack*/
	error = dlm_lock_sync(cinfo->ack_lockres, DLM_LOCK_EX);
	if (error) {
		pr_err("md-cluster: failed to convert CR to EX on ACK(%d)\n",
				error);
		goto failed_ack;
	}

	/*down-convert EX to CR on Ack*/
	error = dlm_lock_sync(cinfo->ack_lockres, DLM_LOCK_CR);
	if (error) {
		pr_err("md-cluster: failed to convert EX to CR on ACK(%d)\n",
				error);
		goto failed_ack;
	}

failed_ack:
	error = dlm_unlock_sync(cinfo->message_lockres);
	if (unlikely(error != 0)) {
		pr_err("md-cluster: failed convert to NL on MESSAGE(%d)\n",
			error);
		/* in case the message can't be released due to some reason */
		goto failed_ack;
	}
failed_message:
	return error;
}