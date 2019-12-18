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
typedef  int /*<<< orphan*/  u8 ;
struct iscsit_transport {int (* iscsit_response_queue ) (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ ) ;} ;
struct iscsi_queue_req {int /*<<< orphan*/  state; struct iscsi_cmd* cmd; } ;
struct iscsi_conn {struct iscsit_transport* conn_transport; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 struct iscsi_queue_req* iscsit_get_cmd_from_response_queue (struct iscsi_conn*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct iscsi_queue_req*) ; 
 int /*<<< orphan*/  lio_qr_cache ; 
 int stub1 (struct iscsi_conn*,struct iscsi_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_handle_response_queue(struct iscsi_conn *conn)
{
	struct iscsit_transport *t = conn->conn_transport;
	struct iscsi_queue_req *qr;
	struct iscsi_cmd *cmd;
	u8 state;
	int ret;

	while ((qr = iscsit_get_cmd_from_response_queue(conn))) {
		cmd = qr->cmd;
		state = qr->state;
		kmem_cache_free(lio_qr_cache, qr);

		ret = t->iscsit_response_queue(conn, cmd, state);
		if (ret == 1 || ret < 0)
			return ret;
	}

	return 0;
}