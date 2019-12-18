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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hinic_pf_to_mgmt {int /*<<< orphan*/  sync_msg_lock; } ;
typedef  enum mgmt_direction_type { ____Placeholder_mgmt_direction_type } mgmt_direction_type ;
typedef  enum hinic_mod_type { ____Placeholder_hinic_mod_type } hinic_mod_type ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_NO_ACK ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int send_msg_to_mgmt (struct hinic_pf_to_mgmt*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int msg_to_mgmt_async(struct hinic_pf_to_mgmt *pf_to_mgmt,
			     enum hinic_mod_type mod, u8 cmd,
			     u8 *buf_in, u16 in_size,
			     enum mgmt_direction_type direction,
			     u16 resp_msg_id)
{
	int err;

	/* Lock the sync_msg_buf */
	down(&pf_to_mgmt->sync_msg_lock);

	err = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_NO_ACK, direction, resp_msg_id);

	up(&pf_to_mgmt->sync_msg_lock);
	return err;
}