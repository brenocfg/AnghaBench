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
struct hinic_recv_msg {int /*<<< orphan*/  recv_done; } ;
struct hinic_pf_to_mgmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mgmt_resp_msg_handler(struct hinic_pf_to_mgmt *pf_to_mgmt,
				  struct hinic_recv_msg *recv_msg)
{
	wmb();  /* verify writing all, before reading */

	complete(&recv_msg->recv_done);
}