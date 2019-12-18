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
struct iscsi_session {int /*<<< orphan*/  frwd_lock; struct iscsi_conn* leadconn; } ;
struct iscsi_conn {int /*<<< orphan*/  suspend_tx; int /*<<< orphan*/  suspend_rx; } ;
struct iscsi_cls_session {struct iscsi_session* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SUSPEND_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int iscsi_conn_bind(struct iscsi_cls_session *cls_session,
		    struct iscsi_cls_conn *cls_conn, int is_leading)
{
	struct iscsi_session *session = cls_session->dd_data;
	struct iscsi_conn *conn = cls_conn->dd_data;

	spin_lock_bh(&session->frwd_lock);
	if (is_leading)
		session->leadconn = conn;
	spin_unlock_bh(&session->frwd_lock);

	/*
	 * Unblock xmitworker(), Login Phase will pass through.
	 */
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_rx);
	clear_bit(ISCSI_SUSPEND_BIT, &conn->suspend_tx);
	return 0;
}