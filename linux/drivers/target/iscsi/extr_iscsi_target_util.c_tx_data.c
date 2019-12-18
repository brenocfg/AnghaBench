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
struct msghdr {int /*<<< orphan*/  msg_iter; } ;
struct kvec {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  sock; int /*<<< orphan*/  conn_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvec*,int,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int sock_sendmsg (int /*<<< orphan*/ ,struct msghdr*) ; 

int tx_data(
	struct iscsi_conn *conn,
	struct kvec *iov,
	int iov_count,
	int data)
{
	struct msghdr msg;
	int total_tx = 0;

	if (!conn || !conn->sock || !conn->conn_ops)
		return -1;

	if (data <= 0) {
		pr_err("Data length is: %d\n", data);
		return -1;
	}

	memset(&msg, 0, sizeof(struct msghdr));

	iov_iter_kvec(&msg.msg_iter, WRITE, iov, iov_count, data);

	while (msg_data_left(&msg)) {
		int tx_loop = sock_sendmsg(conn->sock, &msg);
		if (tx_loop <= 0) {
			pr_debug("tx_loop: %d total_tx %d\n",
				tx_loop, total_tx);
			return tx_loop;
		}
		total_tx += tx_loop;
		pr_debug("tx_loop: %d, total_tx: %d, data: %d\n",
					tx_loop, total_tx, data);
	}

	return total_tx;
}