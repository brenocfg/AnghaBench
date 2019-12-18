#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct isert_conn {int dummy; } ;
struct ib_send_wr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  iscsi_header; struct ib_send_wr send_wr; } ;
struct isert_cmd {TYPE_1__ tx_desc; } ;
struct iscsi_tm_rsp {int dummy; } ;
struct iscsi_conn {struct isert_conn* context; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iscsit_build_task_mgt_rsp (struct iscsi_cmd*,struct iscsi_conn*,struct iscsi_tm_rsp*) ; 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_create_send_desc (struct isert_conn*,struct isert_cmd*,TYPE_1__*) ; 
 int /*<<< orphan*/  isert_dbg (char*,struct isert_conn*) ; 
 int /*<<< orphan*/  isert_init_send_wr (struct isert_conn*,struct isert_cmd*,struct ib_send_wr*) ; 
 int /*<<< orphan*/  isert_init_tx_hdrs (struct isert_conn*,TYPE_1__*) ; 
 int isert_post_response (struct isert_conn*,struct isert_cmd*) ; 

__attribute__((used)) static int
isert_put_tm_rsp(struct iscsi_cmd *cmd, struct iscsi_conn *conn)
{
	struct isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	struct isert_conn *isert_conn = conn->context;
	struct ib_send_wr *send_wr = &isert_cmd->tx_desc.send_wr;

	isert_create_send_desc(isert_conn, isert_cmd, &isert_cmd->tx_desc);
	iscsit_build_task_mgt_rsp(cmd, conn, (struct iscsi_tm_rsp *)
				  &isert_cmd->tx_desc.iscsi_header);
	isert_init_tx_hdrs(isert_conn, &isert_cmd->tx_desc);
	isert_init_send_wr(isert_conn, isert_cmd, send_wr);

	isert_dbg("conn %p Posting Task Management Response\n", isert_conn);

	return isert_post_response(isert_conn, isert_cmd);
}