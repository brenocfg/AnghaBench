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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct iscsi_session {TYPE_1__* sess_ops; int /*<<< orphan*/  nconn; } ;
struct iscsi_conn_recovery {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  cid; struct iscsi_session* sess; } ;
struct TYPE_2__ {int ErrorRecoveryLevel; scalar_t__ MaxConnections; int /*<<< orphan*/  InitiatorName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_LOGIN_STATUS_ISID_ERROR ; 
 int /*<<< orphan*/  ISCSI_STATUS_CLS_INITIATOR_ERR ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsit_connection_reinstatement_rcfr (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_dec_conn_usage_count (struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_discard_cr_cmds_by_expstatsn (struct iscsi_conn_recovery*,int /*<<< orphan*/ ) ; 
 struct iscsi_conn* iscsit_get_conn_from_cid_rcfr (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 struct iscsi_conn_recovery* iscsit_get_inactive_connection_recovery_entry (struct iscsi_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_tx_login_rsp (struct iscsi_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,...) ; 

int iscsi_login_post_auth_non_zero_tsih(
	struct iscsi_conn *conn,
	u16 cid,
	u32 exp_statsn)
{
	struct iscsi_conn *conn_ptr = NULL;
	struct iscsi_conn_recovery *cr = NULL;
	struct iscsi_session *sess = conn->sess;

	/*
	 * By following item 5 in the login table,  if we have found
	 * an existing ISID and a valid/existing TSIH and an existing
	 * CID we do connection reinstatement.  Currently we dont not
	 * support it so we send back an non-zero status class to the
	 * initiator and release the new connection.
	 */
	conn_ptr = iscsit_get_conn_from_cid_rcfr(sess, cid);
	if (conn_ptr) {
		pr_err("Connection exists with CID %hu for %s,"
			" performing connection reinstatement.\n",
			conn_ptr->cid, sess->sess_ops->InitiatorName);

		iscsit_connection_reinstatement_rcfr(conn_ptr);
		iscsit_dec_conn_usage_count(conn_ptr);
	}

	/*
	 * Check for any connection recovery entries containing CID.
	 * We use the original ExpStatSN sent in the first login request
	 * to acknowledge commands for the failed connection.
	 *
	 * Also note that an explict logout may have already been sent,
	 * but the response may not be sent due to additional connection
	 * loss.
	 */
	if (sess->sess_ops->ErrorRecoveryLevel == 2) {
		cr = iscsit_get_inactive_connection_recovery_entry(
				sess, cid);
		if (cr) {
			pr_debug("Performing implicit logout"
				" for connection recovery on CID: %hu\n",
					conn->cid);
			iscsit_discard_cr_cmds_by_expstatsn(cr, exp_statsn);
		}
	}

	/*
	 * Else we follow item 4 from the login table in that we have
	 * found an existing ISID and a valid/existing TSIH and a new
	 * CID we go ahead and continue to add a new connection to the
	 * session.
	 */
	pr_debug("Adding CID %hu to existing session for %s.\n",
			cid, sess->sess_ops->InitiatorName);

	if ((atomic_read(&sess->nconn) + 1) > sess->sess_ops->MaxConnections) {
		pr_err("Adding additional connection to this session"
			" would exceed MaxConnections %d, login failed.\n",
				sess->sess_ops->MaxConnections);
		iscsit_tx_login_rsp(conn, ISCSI_STATUS_CLS_INITIATOR_ERR,
				ISCSI_LOGIN_STATUS_ISID_ERROR);
		return -1;
	}

	return 0;
}