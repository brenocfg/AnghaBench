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
typedef  int /*<<< orphan*/  u64 ;
struct hinic_recv_msg {int dummy; } ;
struct hinic_pf_to_mgmt {struct hinic_recv_msg recv_resp_msg_from_mgmt; struct hinic_recv_msg recv_msg_from_mgmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRECTION ; 
 scalar_t__ HINIC_MSG_HEADER_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MGMT_DIRECT_SEND ; 
 int /*<<< orphan*/  recv_mgmt_msg_handler (struct hinic_pf_to_mgmt*,int /*<<< orphan*/ *,struct hinic_recv_msg*) ; 

__attribute__((used)) static void mgmt_msg_aeqe_handler(void *handle, void *data, u8 size)
{
	struct hinic_pf_to_mgmt *pf_to_mgmt = handle;
	struct hinic_recv_msg *recv_msg;
	u64 *header = (u64 *)data;

	recv_msg = HINIC_MSG_HEADER_GET(*header, DIRECTION) ==
		   MGMT_DIRECT_SEND ?
		   &pf_to_mgmt->recv_msg_from_mgmt :
		   &pf_to_mgmt->recv_resp_msg_from_mgmt;

	recv_mgmt_msg_handler(pf_to_mgmt, header, recv_msg);
}