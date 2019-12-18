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
struct iscsi_data_count {int data_length; int /*<<< orphan*/  iov_count; int /*<<< orphan*/  iov; } ;
struct iscsi_conn {int /*<<< orphan*/  sock; int /*<<< orphan*/  conn_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  iov_iter_kvec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ msg_data_left (struct msghdr*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 
 int sock_recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iscsit_do_rx_data(
	struct iscsi_conn *conn,
	struct iscsi_data_count *count)
{
	int data = count->data_length, rx_loop = 0, total_rx = 0;
	struct msghdr msg;

	if (!conn || !conn->sock || !conn->conn_ops)
		return -1;

	memset(&msg, 0, sizeof(struct msghdr));
	iov_iter_kvec(&msg.msg_iter, READ, count->iov, count->iov_count, data);

	while (msg_data_left(&msg)) {
		rx_loop = sock_recvmsg(conn->sock, &msg, MSG_WAITALL);
		if (rx_loop <= 0) {
			pr_debug("rx_loop: %d total_rx: %d\n",
				rx_loop, total_rx);
			return rx_loop;
		}
		total_rx += rx_loop;
		pr_debug("rx_loop: %d, total_rx: %d, data: %d\n",
				rx_loop, total_rx, data);
	}

	return total_rx;
}