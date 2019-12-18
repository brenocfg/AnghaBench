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
struct sock {int /*<<< orphan*/  sk_callback_lock; struct iscsi_conn* sk_user_data; } ;
struct iscsi_conn {void (* orig_state_change ) (struct sock*) ;int /*<<< orphan*/  login_work; int /*<<< orphan*/  login_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGIN_FLAGS_CLOSED ; 
 int /*<<< orphan*/  LOGIN_FLAGS_INITIAL_PDU ; 
 int /*<<< orphan*/  LOGIN_FLAGS_READY ; 
 int /*<<< orphan*/  LOGIN_FLAGS_READ_ACTIVE ; 
 int __iscsi_target_sk_check_close (struct sock*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iscsi_target_sk_state_change(struct sock *sk)
{
	struct iscsi_conn *conn;
	void (*orig_state_change)(struct sock *);
	bool state;

	pr_debug("Entering iscsi_target_sk_state_change\n");

	write_lock_bh(&sk->sk_callback_lock);
	conn = sk->sk_user_data;
	if (!conn) {
		write_unlock_bh(&sk->sk_callback_lock);
		return;
	}
	orig_state_change = conn->orig_state_change;

	if (!test_bit(LOGIN_FLAGS_READY, &conn->login_flags)) {
		pr_debug("Got LOGIN_FLAGS_READY=0 sk_state_change conn: %p\n",
			 conn);
		write_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		return;
	}
	state = __iscsi_target_sk_check_close(sk);
	pr_debug("__iscsi_target_sk_close_change: state: %d\n", state);

	if (test_bit(LOGIN_FLAGS_READ_ACTIVE, &conn->login_flags)) {
		pr_debug("Got LOGIN_FLAGS_READ_ACTIVE=1 sk_state_change"
			 " conn: %p\n", conn);
		if (state)
			set_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags);
		write_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		return;
	}
	if (test_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags)) {
		pr_debug("Got LOGIN_FLAGS_CLOSED=1 sk_state_change conn: %p\n",
			 conn);
		write_unlock_bh(&sk->sk_callback_lock);
		orig_state_change(sk);
		return;
	}
	/*
	 * If the TCP connection has dropped, go ahead and set LOGIN_FLAGS_CLOSED,
	 * but only queue conn->login_work -> iscsi_target_do_login_rx()
	 * processing if LOGIN_FLAGS_INITIAL_PDU has already been cleared.
	 *
	 * When iscsi_target_do_login_rx() runs, iscsi_target_sk_check_close()
	 * will detect the dropped TCP connection from delayed workqueue context.
	 *
	 * If LOGIN_FLAGS_INITIAL_PDU is still set, which means the initial
	 * iscsi_target_start_negotiation() is running, iscsi_target_do_login()
	 * via iscsi_target_sk_check_close() or iscsi_target_start_negotiation()
	 * via iscsi_target_sk_check_and_clear() is responsible for detecting the
	 * dropped TCP connection in iscsi_np process context, and cleaning up
	 * the remaining iscsi connection resources.
	 */
	if (state) {
		pr_debug("iscsi_target_sk_state_change got failed state\n");
		set_bit(LOGIN_FLAGS_CLOSED, &conn->login_flags);
		state = test_bit(LOGIN_FLAGS_INITIAL_PDU, &conn->login_flags);
		write_unlock_bh(&sk->sk_callback_lock);

		orig_state_change(sk);

		if (!state)
			schedule_delayed_work(&conn->login_work, 0);
		return;
	}
	write_unlock_bh(&sk->sk_callback_lock);

	orig_state_change(sk);
}