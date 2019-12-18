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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct socket {TYPE_1__* sk; TYPE_3__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {scalar_t__ sin_family; TYPE_2__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int (* getname ) (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int sk_protocol; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int stub1 (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 

int usnic_transport_sock_get_addr(struct socket *sock, int *proto,
					uint32_t *addr, uint16_t *port)
{
	int err;
	struct sockaddr_in sock_addr;

	err = sock->ops->getname(sock,
				(struct sockaddr *)&sock_addr,
				0);
	if (err < 0)
		return err;

	if (sock_addr.sin_family != AF_INET)
		return -EINVAL;

	if (proto)
		*proto = sock->sk->sk_protocol;
	if (port)
		*port = ntohs(((struct sockaddr_in *)&sock_addr)->sin_port);
	if (addr)
		*addr = ntohl(((struct sockaddr_in *)
					&sock_addr)->sin_addr.s_addr);

	return 0;
}