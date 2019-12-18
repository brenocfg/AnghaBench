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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; } ;
struct sockaddr {int sa_family; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int IPV6_ADDR_LINKLOCAL ; 
 int ib_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cma_addr_cmp(const struct sockaddr *src, const struct sockaddr *dst)
{
	if (src->sa_family != dst->sa_family)
		return -1;

	switch (src->sa_family) {
	case AF_INET:
		return ((struct sockaddr_in *)src)->sin_addr.s_addr !=
		       ((struct sockaddr_in *)dst)->sin_addr.s_addr;
	case AF_INET6: {
		struct sockaddr_in6 *src_addr6 = (struct sockaddr_in6 *)src;
		struct sockaddr_in6 *dst_addr6 = (struct sockaddr_in6 *)dst;
		bool link_local;

		if (ipv6_addr_cmp(&src_addr6->sin6_addr,
					  &dst_addr6->sin6_addr))
			return 1;
		link_local = ipv6_addr_type(&dst_addr6->sin6_addr) &
			     IPV6_ADDR_LINKLOCAL;
		/* Link local must match their scope_ids */
		return link_local ? (src_addr6->sin6_scope_id !=
				     dst_addr6->sin6_scope_id) :
				    0;
	}

	default:
		return ib_addr_cmp(&((struct sockaddr_ib *) src)->sib_addr,
				   &((struct sockaddr_ib *) dst)->sib_addr);
	}
}