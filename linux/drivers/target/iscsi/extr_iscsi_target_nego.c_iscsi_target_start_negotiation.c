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
struct sock {int /*<<< orphan*/  sk_callback_lock; } ;
struct iscsi_login {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  login_work; int /*<<< orphan*/  login_flags; TYPE_1__* sock; } ;
struct TYPE_2__ {struct sock* sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGIN_FLAGS_INITIAL_PDU ; 
 int /*<<< orphan*/  LOGIN_FLAGS_READY ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_remove_failed_auth_entry (struct iscsi_conn*) ; 
 int iscsi_target_do_login (struct iscsi_conn*,struct iscsi_login*) ; 
 int /*<<< orphan*/  iscsi_target_nego_release (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsi_target_restore_sock_callbacks (struct iscsi_conn*) ; 
 scalar_t__ iscsi_target_sk_check_and_clear (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int iscsi_target_start_negotiation(
	struct iscsi_login *login,
	struct iscsi_conn *conn)
{
	int ret;

	if (conn->sock) {
		struct sock *sk = conn->sock->sk;

		write_lock_bh(&sk->sk_callback_lock);
		set_bit(LOGIN_FLAGS_READY, &conn->login_flags);
		set_bit(LOGIN_FLAGS_INITIAL_PDU, &conn->login_flags);
		write_unlock_bh(&sk->sk_callback_lock);
	}
	/*
	 * If iscsi_target_do_login returns zero to signal more PDU
	 * exchanges are required to complete the login, go ahead and
	 * clear LOGIN_FLAGS_INITIAL_PDU but only if the TCP connection
	 * is still active.
	 *
	 * Otherwise if TCP connection dropped asynchronously, go ahead
	 * and perform connection cleanup now.
	 */
	ret = iscsi_target_do_login(conn, login);
	if (!ret && iscsi_target_sk_check_and_clear(conn, LOGIN_FLAGS_INITIAL_PDU))
		ret = -1;

	if (ret < 0) {
		cancel_delayed_work_sync(&conn->login_work);
		iscsi_target_restore_sock_callbacks(conn);
		iscsi_remove_failed_auth_entry(conn);
	}
	if (ret != 0)
		iscsi_target_nego_release(conn);

	return ret;
}