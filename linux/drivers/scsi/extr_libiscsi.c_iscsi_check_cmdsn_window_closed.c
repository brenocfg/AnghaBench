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
struct iscsi_session {int /*<<< orphan*/  queued_cmdsn; int /*<<< orphan*/  cmdsn; int /*<<< orphan*/  max_cmdsn; int /*<<< orphan*/  exp_cmdsn; } ;
struct iscsi_conn {struct iscsi_session* session; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  ISCSI_DBG_SESSION (struct iscsi_session*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_sna_lte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsi_check_cmdsn_window_closed(struct iscsi_conn *conn)
{
	struct iscsi_session *session = conn->session;

	/*
	 * Check for iSCSI window and take care of CmdSN wrap-around
	 */
	if (!iscsi_sna_lte(session->queued_cmdsn, session->max_cmdsn)) {
		ISCSI_DBG_SESSION(session, "iSCSI CmdSN closed. ExpCmdSn "
				  "%u MaxCmdSN %u CmdSN %u/%u\n",
				  session->exp_cmdsn, session->max_cmdsn,
				  session->cmdsn, session->queued_cmdsn);
		return -ENOSPC;
	}
	return 0;
}