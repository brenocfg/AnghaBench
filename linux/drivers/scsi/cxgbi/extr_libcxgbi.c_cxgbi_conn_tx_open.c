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
struct iscsi_conn {int /*<<< orphan*/  id; } ;
struct cxgbi_sock {struct iscsi_conn* user_data; } ;

/* Variables and functions */
 int CXGBI_DBG_SOCK ; 
 int /*<<< orphan*/  iscsi_conn_queue_work (struct iscsi_conn*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct cxgbi_sock*,int /*<<< orphan*/ ) ; 

void cxgbi_conn_tx_open(struct cxgbi_sock *csk)
{
	struct iscsi_conn *conn = csk->user_data;

	if (conn) {
		log_debug(1 << CXGBI_DBG_SOCK,
			"csk 0x%p, cid %d.\n", csk, conn->id);
		iscsi_conn_queue_work(conn);
	}
}