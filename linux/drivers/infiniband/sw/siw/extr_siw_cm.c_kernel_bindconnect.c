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
struct socket {TYPE_1__* ops; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  s_val ;
struct TYPE_2__ {int (* bind ) (struct socket*,struct sockaddr*,size_t) ;int (* connect ) (struct socket*,struct sockaddr*,size_t,int) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int stub1 (struct socket*,struct sockaddr*,size_t) ; 
 int stub2 (struct socket*,struct sockaddr*,size_t,int) ; 

__attribute__((used)) static int kernel_bindconnect(struct socket *s, struct sockaddr *laddr,
			      struct sockaddr *raddr)
{
	int rv, flags = 0, s_val = 1;
	size_t size = laddr->sa_family == AF_INET ?
		sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);

	/*
	 * Make address available again asap.
	 */
	rv = kernel_setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&s_val,
			       sizeof(s_val));
	if (rv < 0)
		return rv;

	rv = s->ops->bind(s, laddr, size);
	if (rv < 0)
		return rv;

	rv = s->ops->connect(s, raddr, size, flags);

	return rv < 0 ? rv : 0;
}