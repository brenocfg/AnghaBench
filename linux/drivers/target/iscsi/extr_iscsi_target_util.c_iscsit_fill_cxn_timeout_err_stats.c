#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cxn_timeout_errors; int /*<<< orphan*/  last_sess_failure_type; int /*<<< orphan*/  last_sess_fail_rem_name; } ;
struct iscsi_tiqn {TYPE_2__ sess_err_stats; } ;
struct iscsi_session {int /*<<< orphan*/  conn_timeout_errors; TYPE_1__* sess_ops; struct iscsi_portal_group* tpg; } ;
struct iscsi_portal_group {struct iscsi_tiqn* tpg_tiqn; } ;
struct TYPE_3__ {int /*<<< orphan*/  InitiatorName; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_SESS_ERR_CXN_TIMEOUT ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iscsit_fill_cxn_timeout_err_stats(struct iscsi_session *sess)
{
	struct iscsi_portal_group *tpg = sess->tpg;
	struct iscsi_tiqn *tiqn = tpg->tpg_tiqn;

	if (!tiqn)
		return;

	spin_lock_bh(&tiqn->sess_err_stats.lock);
	strlcpy(tiqn->sess_err_stats.last_sess_fail_rem_name,
			sess->sess_ops->InitiatorName,
			sizeof(tiqn->sess_err_stats.last_sess_fail_rem_name));
	tiqn->sess_err_stats.last_sess_failure_type =
			ISCSI_SESS_ERR_CXN_TIMEOUT;
	tiqn->sess_err_stats.cxn_timeout_errors++;
	atomic_long_inc(&sess->conn_timeout_errors);
	spin_unlock_bh(&tiqn->sess_err_stats.lock);
}