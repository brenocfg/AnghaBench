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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_scope_id; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_ib {int /*<<< orphan*/  sib_pkey; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  bound_dev_if; } ;
struct TYPE_5__ {TYPE_1__ dev_addr; int /*<<< orphan*/  src_addr; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;
struct rdma_cm_id {TYPE_3__ route; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int IPV6_ADDR_LINKLOCAL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int ipv6_addr_type (int /*<<< orphan*/ *) ; 
 int rdma_bind_addr (struct rdma_cm_id*,struct sockaddr*) ; 

__attribute__((used)) static int cma_bind_addr(struct rdma_cm_id *id, struct sockaddr *src_addr,
			 const struct sockaddr *dst_addr)
{
	if (!src_addr || !src_addr->sa_family) {
		src_addr = (struct sockaddr *) &id->route.addr.src_addr;
		src_addr->sa_family = dst_addr->sa_family;
		if (IS_ENABLED(CONFIG_IPV6) &&
		    dst_addr->sa_family == AF_INET6) {
			struct sockaddr_in6 *src_addr6 = (struct sockaddr_in6 *) src_addr;
			struct sockaddr_in6 *dst_addr6 = (struct sockaddr_in6 *) dst_addr;
			src_addr6->sin6_scope_id = dst_addr6->sin6_scope_id;
			if (ipv6_addr_type(&dst_addr6->sin6_addr) & IPV6_ADDR_LINKLOCAL)
				id->route.addr.dev_addr.bound_dev_if = dst_addr6->sin6_scope_id;
		} else if (dst_addr->sa_family == AF_IB) {
			((struct sockaddr_ib *) src_addr)->sib_pkey =
				((struct sockaddr_ib *) dst_addr)->sib_pkey;
		}
	}
	return rdma_bind_addr(id, src_addr);
}