#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct se_portal_group {int /*<<< orphan*/  session_lock; } ;
struct iscsi_np {int dummy; } ;
struct iscsi_conn {TYPE_2__* conn_transport; int /*<<< orphan*/ * sock; int /*<<< orphan*/ * param_list; scalar_t__ conn_rx_hash; scalar_t__ conn_tx_hash; TYPE_3__* sess; TYPE_1__* tpg; } ;
struct crypto_ahash {int dummy; } ;
struct TYPE_8__ {scalar_t__ session_state; int /*<<< orphan*/  conn_lock; int /*<<< orphan*/  session_continuation; struct TYPE_8__* sess_ops; int /*<<< orphan*/  session_index; int /*<<< orphan*/  se_sess; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* iscsit_free_conn ) (struct iscsi_conn*) ;int /*<<< orphan*/  (* iscsit_wait_conn ) (struct iscsi_conn*) ;} ;
struct TYPE_6__ {struct se_portal_group tpg_se_tpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_LOGIN_STATUS_INIT_ERR ; 
 int /*<<< orphan*/  ISCSI_STATUS_CLS_INITIATOR_ERR ; 
 scalar_t__ TARG_SESS_STATE_FAILED ; 
 int /*<<< orphan*/  ahash_request_free (scalar_t__) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct crypto_ahash* crypto_ahash_reqtfm (scalar_t__) ; 
 int /*<<< orphan*/  crypto_free_ahash (struct crypto_ahash*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_release_param_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_stop_login_thread_timer (struct iscsi_np*) ; 
 int /*<<< orphan*/  iscsi_target_nego_release (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_collect_login_stats (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_dec_session_usage_count (TYPE_3__*) ; 
 int /*<<< orphan*/  iscsit_free_conn (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_start_time2retain_handler (TYPE_3__*) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  sess_ida ; 
 int /*<<< orphan*/  sock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_conn*) ; 
 int /*<<< orphan*/  stub2 (struct iscsi_conn*) ; 
 int /*<<< orphan*/  transport_free_session (int /*<<< orphan*/ ) ; 

void iscsi_target_login_sess_out(struct iscsi_conn *conn,
		struct iscsi_np *np, bool zero_tsih, bool new_sess)
{
	if (!new_sess)
		goto old_sess_out;

	pr_err("iSCSI Login negotiation failed.\n");
	iscsit_collect_login_stats(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				   ISCSI_LOGIN_STATUS_INIT_ERR);
	if (!zero_tsih || !conn->sess)
		goto old_sess_out;

	transport_free_session(conn->sess->se_sess);
	ida_free(&sess_ida, conn->sess->session_index);
	kfree(conn->sess->sess_ops);
	kfree(conn->sess);
	conn->sess = NULL;

old_sess_out:
	iscsi_stop_login_thread_timer(np);
	/*
	 * If login negotiation fails check if the Time2Retain timer
	 * needs to be restarted.
	 */
	if (!zero_tsih && conn->sess) {
		spin_lock_bh(&conn->sess->conn_lock);
		if (conn->sess->session_state == TARG_SESS_STATE_FAILED) {
			struct se_portal_group *se_tpg =
					&conn->tpg->tpg_se_tpg;

			atomic_set(&conn->sess->session_continuation, 0);
			spin_unlock_bh(&conn->sess->conn_lock);
			spin_lock_bh(&se_tpg->session_lock);
			iscsit_start_time2retain_handler(conn->sess);
			spin_unlock_bh(&se_tpg->session_lock);
		} else
			spin_unlock_bh(&conn->sess->conn_lock);
		iscsit_dec_session_usage_count(conn->sess);
	}

	ahash_request_free(conn->conn_tx_hash);
	if (conn->conn_rx_hash) {
		struct crypto_ahash *tfm;

		tfm = crypto_ahash_reqtfm(conn->conn_rx_hash);
		ahash_request_free(conn->conn_rx_hash);
		crypto_free_ahash(tfm);
	}

	if (conn->param_list) {
		iscsi_release_param_list(conn->param_list);
		conn->param_list = NULL;
	}
	iscsi_target_nego_release(conn);

	if (conn->sock) {
		sock_release(conn->sock);
		conn->sock = NULL;
	}

	if (conn->conn_transport->iscsit_wait_conn)
		conn->conn_transport->iscsit_wait_conn(conn);

	if (conn->conn_transport->iscsit_free_conn)
		conn->conn_transport->iscsit_free_conn(conn);

	iscsit_free_conn(conn);
}