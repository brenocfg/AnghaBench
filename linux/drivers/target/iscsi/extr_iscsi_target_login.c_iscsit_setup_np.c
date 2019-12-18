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
struct socket {int dummy; } ;
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct iscsi_np {int np_network_transport; struct socket* np_socket; int /*<<< orphan*/  np_sockaddr; void* np_ip_proto; void* np_sock_type; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int EINVAL ; 
 void* IPPROTO_IP ; 
 void* IPPROTO_SCTP ; 
 void* IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_FREEBIND ; 
 int ISCSIT_TCP_BACKLOG ; 
#define  ISCSI_SCTP_TCP 130 
#define  ISCSI_SCTP_UDP 129 
#define  ISCSI_TCP 128 
 void* SOCK_SEQPACKET ; 
 void* SOCK_STREAM ; 
 void* SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_listen (struct socket*,int) ; 
 int kernel_setsockopt (struct socket*,void*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int sock_create (scalar_t__,void*,void*,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

int iscsit_setup_np(
	struct iscsi_np *np,
	struct sockaddr_storage *sockaddr)
{
	struct socket *sock = NULL;
	int backlog = ISCSIT_TCP_BACKLOG, ret, opt = 0, len;

	switch (np->np_network_transport) {
	case ISCSI_TCP:
		np->np_ip_proto = IPPROTO_TCP;
		np->np_sock_type = SOCK_STREAM;
		break;
	case ISCSI_SCTP_TCP:
		np->np_ip_proto = IPPROTO_SCTP;
		np->np_sock_type = SOCK_STREAM;
		break;
	case ISCSI_SCTP_UDP:
		np->np_ip_proto = IPPROTO_SCTP;
		np->np_sock_type = SOCK_SEQPACKET;
		break;
	default:
		pr_err("Unsupported network_transport: %d\n",
				np->np_network_transport);
		return -EINVAL;
	}

	ret = sock_create(sockaddr->ss_family, np->np_sock_type,
			np->np_ip_proto, &sock);
	if (ret < 0) {
		pr_err("sock_create() failed.\n");
		return ret;
	}
	np->np_socket = sock;
	/*
	 * Setup the np->np_sockaddr from the passed sockaddr setup
	 * in iscsi_target_configfs.c code..
	 */
	memcpy(&np->np_sockaddr, sockaddr,
			sizeof(struct sockaddr_storage));

	if (sockaddr->ss_family == AF_INET6)
		len = sizeof(struct sockaddr_in6);
	else
		len = sizeof(struct sockaddr_in);
	/*
	 * Set SO_REUSEADDR, and disable Nagel Algorithm with TCP_NODELAY.
	 */
	/* FIXME: Someone please explain why this is endian-safe */
	opt = 1;
	if (np->np_network_transport == ISCSI_TCP) {
		ret = kernel_setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
				(char *)&opt, sizeof(opt));
		if (ret < 0) {
			pr_err("kernel_setsockopt() for TCP_NODELAY"
				" failed: %d\n", ret);
			goto fail;
		}
	}

	/* FIXME: Someone please explain why this is endian-safe */
	ret = kernel_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
			(char *)&opt, sizeof(opt));
	if (ret < 0) {
		pr_err("kernel_setsockopt() for SO_REUSEADDR"
			" failed\n");
		goto fail;
	}

	ret = kernel_setsockopt(sock, IPPROTO_IP, IP_FREEBIND,
			(char *)&opt, sizeof(opt));
	if (ret < 0) {
		pr_err("kernel_setsockopt() for IP_FREEBIND"
			" failed\n");
		goto fail;
	}

	ret = kernel_bind(sock, (struct sockaddr *)&np->np_sockaddr, len);
	if (ret < 0) {
		pr_err("kernel_bind() failed: %d\n", ret);
		goto fail;
	}

	ret = kernel_listen(sock, backlog);
	if (ret != 0) {
		pr_err("kernel_listen() failed: %d\n", ret);
		goto fail;
	}

	return 0;
fail:
	np->np_socket = NULL;
	sock_release(sock);
	return ret;
}