#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* ops; } ;
struct TYPE_6__ {struct sockaddr_in6* s6_addr32; } ;
struct sockaddr_in6 {TYPE_3__ sin6_addr; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin_port; void* sin_family; } ;
struct sockaddr_in {TYPE_3__ sin6_addr; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin_port; void* sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_4__ {scalar_t__ ss_family; } ;
struct iscsi_np {TYPE_1__ np_sockaddr; struct socket* np_socket; } ;
struct iscsi_conn {scalar_t__ login_family; int /*<<< orphan*/  local_sockaddr; struct socket* sock; int /*<<< orphan*/  login_sockaddr; } ;
typedef  int /*<<< orphan*/  sock_in6 ;
typedef  int /*<<< orphan*/  sock_in ;
struct TYPE_5__ {int (* getname ) (struct socket*,struct sockaddr*,int) ;} ;

/* Variables and functions */
 void* AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  ipv6_addr_v4mapped (TYPE_3__*) ; 
 int kernel_accept (struct socket*,struct socket**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_in6*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 
 int stub2 (struct socket*,struct sockaddr*,int) ; 
 int stub3 (struct socket*,struct sockaddr*,int) ; 
 int stub4 (struct socket*,struct sockaddr*,int) ; 

int iscsit_accept_np(struct iscsi_np *np, struct iscsi_conn *conn)
{
	struct socket *new_sock, *sock = np->np_socket;
	struct sockaddr_in sock_in;
	struct sockaddr_in6 sock_in6;
	int rc;

	rc = kernel_accept(sock, &new_sock, 0);
	if (rc < 0)
		return rc;

	conn->sock = new_sock;
	conn->login_family = np->np_sockaddr.ss_family;

	if (np->np_sockaddr.ss_family == AF_INET6) {
		memset(&sock_in6, 0, sizeof(struct sockaddr_in6));

		rc = conn->sock->ops->getname(conn->sock,
				(struct sockaddr *)&sock_in6, 1);
		if (rc >= 0) {
			if (!ipv6_addr_v4mapped(&sock_in6.sin6_addr)) {
				memcpy(&conn->login_sockaddr, &sock_in6, sizeof(sock_in6));
			} else {
				/* Pretend to be an ipv4 socket */
				sock_in.sin_family = AF_INET;
				sock_in.sin_port = sock_in6.sin6_port;
				memcpy(&sock_in.sin_addr, &sock_in6.sin6_addr.s6_addr32[3], 4);
				memcpy(&conn->login_sockaddr, &sock_in, sizeof(sock_in));
			}
		}

		rc = conn->sock->ops->getname(conn->sock,
				(struct sockaddr *)&sock_in6, 0);
		if (rc >= 0) {
			if (!ipv6_addr_v4mapped(&sock_in6.sin6_addr)) {
				memcpy(&conn->local_sockaddr, &sock_in6, sizeof(sock_in6));
			} else {
				/* Pretend to be an ipv4 socket */
				sock_in.sin_family = AF_INET;
				sock_in.sin_port = sock_in6.sin6_port;
				memcpy(&sock_in.sin_addr, &sock_in6.sin6_addr.s6_addr32[3], 4);
				memcpy(&conn->local_sockaddr, &sock_in, sizeof(sock_in));
			}
		}
	} else {
		memset(&sock_in, 0, sizeof(struct sockaddr_in));

		rc = conn->sock->ops->getname(conn->sock,
				(struct sockaddr *)&sock_in, 1);
		if (rc >= 0)
			memcpy(&conn->login_sockaddr, &sock_in, sizeof(sock_in));

		rc = conn->sock->ops->getname(conn->sock,
				(struct sockaddr *)&sock_in, 0);
		if (rc >= 0)
			memcpy(&conn->local_sockaddr, &sock_in, sizeof(sock_in));
	}

	return 0;
}