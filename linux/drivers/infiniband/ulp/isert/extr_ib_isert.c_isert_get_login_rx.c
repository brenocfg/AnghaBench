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
struct isert_conn {int /*<<< orphan*/  login_comp; int /*<<< orphan*/  login_req_comp; struct isert_conn* context; } ;
struct iscsi_login {struct isert_conn* req; int /*<<< orphan*/  first_request; } ;
struct iscsi_conn {int /*<<< orphan*/  login_comp; int /*<<< orphan*/  login_req_comp; struct iscsi_conn* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  isert_err (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_rx_login_req (struct isert_conn*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isert_get_login_rx(struct iscsi_conn *conn, struct iscsi_login *login)
{
	struct isert_conn *isert_conn = conn->context;
	int ret;

	isert_info("before login_req comp conn: %p\n", isert_conn);
	ret = wait_for_completion_interruptible(&isert_conn->login_req_comp);
	if (ret) {
		isert_err("isert_conn %p interrupted before got login req\n",
			  isert_conn);
		return ret;
	}
	reinit_completion(&isert_conn->login_req_comp);

	/*
	 * For login requests after the first PDU, isert_rx_login_req() will
	 * kick schedule_delayed_work(&conn->login_work) as the packet is
	 * received, which turns this callback from iscsi_target_do_login_rx()
	 * into a NOP.
	 */
	if (!login->first_request)
		return 0;

	isert_rx_login_req(isert_conn);

	isert_info("before login_comp conn: %p\n", conn);
	ret = wait_for_completion_interruptible(&isert_conn->login_comp);
	if (ret)
		return ret;

	isert_info("processing login->req: %p\n", login->req);

	return 0;
}