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
struct kvec {int dummy; } ;
struct iscsi_data_count {int iov_count; int data_length; int /*<<< orphan*/  type; struct kvec* iov; } ;
struct iscsi_conn {int /*<<< orphan*/  conn_ops; int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_RX_DATA ; 
 int iscsit_do_rx_data (struct iscsi_conn*,struct iscsi_data_count*) ; 
 int /*<<< orphan*/  memset (struct iscsi_data_count*,int /*<<< orphan*/ ,int) ; 

int rx_data(
	struct iscsi_conn *conn,
	struct kvec *iov,
	int iov_count,
	int data)
{
	struct iscsi_data_count c;

	if (!conn || !conn->sock || !conn->conn_ops)
		return -1;

	memset(&c, 0, sizeof(struct iscsi_data_count));
	c.iov = iov;
	c.iov_count = iov_count;
	c.data_length = data;
	c.type = ISCSI_RX_DATA;

	return iscsit_do_rx_data(conn, &c);
}