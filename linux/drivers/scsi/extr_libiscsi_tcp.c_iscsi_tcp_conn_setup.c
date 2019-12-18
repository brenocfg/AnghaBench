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
typedef  int /*<<< orphan*/  uint32_t ;
struct iscsi_tcp_conn {struct iscsi_tcp_conn* dd_data; struct iscsi_conn* iscsi_conn; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; int /*<<< orphan*/  max_recv_dlength; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 struct iscsi_cls_conn* iscsi_conn_setup (struct iscsi_cls_session*,int,int /*<<< orphan*/ ) ; 

struct iscsi_cls_conn *
iscsi_tcp_conn_setup(struct iscsi_cls_session *cls_session, int dd_data_size,
		      uint32_t conn_idx)

{
	struct iscsi_conn *conn;
	struct iscsi_cls_conn *cls_conn;
	struct iscsi_tcp_conn *tcp_conn;

	cls_conn = iscsi_conn_setup(cls_session,
				    sizeof(*tcp_conn) + dd_data_size, conn_idx);
	if (!cls_conn)
		return NULL;
	conn = cls_conn->dd_data;
	/*
	 * due to strange issues with iser these are not set
	 * in iscsi_conn_setup
	 */
	conn->max_recv_dlength = ISCSI_DEF_MAX_RECV_SEG_LEN;

	tcp_conn = conn->dd_data;
	tcp_conn->iscsi_conn = conn;
	tcp_conn->dd_data = conn->dd_data + sizeof(*tcp_conn);
	return cls_conn;
}