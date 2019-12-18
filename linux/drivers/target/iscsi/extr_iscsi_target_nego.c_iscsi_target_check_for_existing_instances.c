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
struct iscsi_login {int checked_for_existing; int /*<<< orphan*/  initial_exp_statsn; int /*<<< orphan*/  cid; int /*<<< orphan*/  tsih; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int iscsi_check_for_session_reinstatement (struct iscsi_conn*) ; 
 int iscsi_login_post_auth_non_zero_tsih (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_target_check_for_existing_instances(
	struct iscsi_conn *conn,
	struct iscsi_login *login)
{
	if (login->checked_for_existing)
		return 0;

	login->checked_for_existing = 1;

	if (!login->tsih)
		return iscsi_check_for_session_reinstatement(conn);
	else
		return iscsi_login_post_auth_non_zero_tsih(conn, login->cid,
				login->initial_exp_statsn);
}