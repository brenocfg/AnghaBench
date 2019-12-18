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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct iscsi_tcp_conn {struct iscsi_sw_tcp_conn* dd_data; } ;
struct iscsi_sw_tcp_host {struct iscsi_session* session; } ;
struct iscsi_sw_tcp_conn {int /*<<< orphan*/  sock; } ;
struct iscsi_session {int /*<<< orphan*/  frwd_lock; struct iscsi_conn* leadconn; } ;
struct iscsi_conn {struct iscsi_tcp_conn* dd_data; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum iscsi_param { ____Placeholder_iscsi_param } iscsi_param ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;

/* Variables and functions */
 int ENOTCONN ; 
#define  ISCSI_HOST_PARAM_IPADDRESS 128 
 int iscsi_conn_get_addr_param (struct sockaddr_storage*,int,char*) ; 
 int iscsi_host_get_param (struct Scsi_Host*,int,char*) ; 
 struct iscsi_sw_tcp_host* iscsi_host_priv (struct Scsi_Host*) ; 
 int kernel_getsockname (int /*<<< orphan*/ ,struct sockaddr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsi_sw_tcp_host_get_param(struct Scsi_Host *shost,
				       enum iscsi_host_param param, char *buf)
{
	struct iscsi_sw_tcp_host *tcp_sw_host = iscsi_host_priv(shost);
	struct iscsi_session *session = tcp_sw_host->session;
	struct iscsi_conn *conn;
	struct iscsi_tcp_conn *tcp_conn;
	struct iscsi_sw_tcp_conn *tcp_sw_conn;
	struct sockaddr_in6 addr;
	int rc;

	switch (param) {
	case ISCSI_HOST_PARAM_IPADDRESS:
		if (!session)
			return -ENOTCONN;

		spin_lock_bh(&session->frwd_lock);
		conn = session->leadconn;
		if (!conn) {
			spin_unlock_bh(&session->frwd_lock);
			return -ENOTCONN;
		}
		tcp_conn = conn->dd_data;

		tcp_sw_conn = tcp_conn->dd_data;
		if (!tcp_sw_conn->sock) {
			spin_unlock_bh(&session->frwd_lock);
			return -ENOTCONN;
		}

		rc = kernel_getsockname(tcp_sw_conn->sock,
					(struct sockaddr *)&addr);
		spin_unlock_bh(&session->frwd_lock);
		if (rc < 0)
			return rc;

		return iscsi_conn_get_addr_param((struct sockaddr_storage *)
						 &addr,
						 (enum iscsi_param)param, buf);
	default:
		return iscsi_host_get_param(shost, param, buf);
	}

	return 0;
}