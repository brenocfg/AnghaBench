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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vc_sm_lock_unlock_t {int dummy; } ;
struct sm_instance {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_SM_MSG_TYPE_UNLOCK ; 
 int /*<<< orphan*/  VC_SM_MSG_TYPE_UNLOCK_NOANS ; 
 int vc_vchi_sm_send_msg (struct sm_instance*,int /*<<< orphan*/ ,struct vc_sm_lock_unlock_t*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

int vc_vchi_sm_unlock(struct sm_instance *handle,
		      struct vc_sm_lock_unlock_t *msg,
		      uint32_t *cur_trans_id, uint8_t wait_reply)
{
	return vc_vchi_sm_send_msg(handle, wait_reply ?
				   VC_SM_MSG_TYPE_UNLOCK :
				   VC_SM_MSG_TYPE_UNLOCK_NOANS, msg,
				   sizeof(*msg), 0, 0, cur_trans_id,
				   wait_reply);
}