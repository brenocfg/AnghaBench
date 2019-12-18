#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_conn {int /*<<< orphan*/  sock; } ;
struct iscsi_conn {TYPE_1__* session; struct iscsi_tcp_conn* dd_data; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;
struct TYPE_2__ {int /*<<< orphan*/  frwd_lock; } ;

/* Variables and functions */
 int ENOTCONN ; 
#define  ISCSI_PARAM_CONN_ADDRESS 130 
#define  ISCSI_PARAM_CONN_PORT 129 
#define  ISCSI_PARAM_LOCAL_PORT 128 
 int iscsi_conn_get_addr_param (struct sockaddr_storage*,int,char*) ; 
 int iscsi_conn_get_param (struct iscsi_cls_conn*,int,char*) ; 
 int kernel_getpeername (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int kernel_getsockname (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_sw_tcp_conn_get_param(struct iscsi_cls_conn *cls_conn,
				       enum iscsi_param param, char *buf)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct iscsi_tcp_conn *tcp_conn = conn->dd_data;
	struct iscsi_sw_tcp_conn *tcp_sw_conn = tcp_conn->dd_data;
	struct sockaddr_in6 addr;
	int rc;

	switch(param) {
	case ISCSI_PARAM_CONN_PORT:
	case ISCSI_PARAM_CONN_ADDRESS:
	case ISCSI_PARAM_LOCAL_PORT:
		spin_lock_bh(&conn->session->frwd_lock);
		if (!tcp_sw_conn || !tcp_sw_conn->sock) {
			spin_unlock_bh(&conn->session->frwd_lock);
			return -ENOTCONN;
		}
		if (param == ISCSI_PARAM_LOCAL_PORT)
			rc = kernel_getsockname(tcp_sw_conn->sock,
						(struct sockaddr *)&addr);
		else
			rc = kernel_getpeername(tcp_sw_conn->sock,
						(struct sockaddr *)&addr);
		spin_unlock_bh(&conn->session->frwd_lock);
		if (rc < 0)
			return rc;

		return iscsi_conn_get_addr_param((struct sockaddr_storage *)
						 &addr, param, buf);
	default:
		return iscsi_conn_get_param(cls_conn, param, buf);
	}

	return 0;
}