#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
struct rdma_dev_addr {int dummy; } ;
struct dst_entry {TYPE_2__* dev; } ;
typedef  scalar_t__ sa_family_t ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ ARPHRD_INFINIBAND ; 
 int dst_fetch_ha (struct dst_entry const*,struct rdma_dev_addr*,void const*) ; 
 scalar_t__ has_gateway (struct dst_entry const*,scalar_t__) ; 
 int ib_nl_fetch_ha (struct dst_entry const*,struct rdma_dev_addr*,void const*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int fetch_ha(const struct dst_entry *dst, struct rdma_dev_addr *dev_addr,
		    const struct sockaddr *dst_in, u32 seq)
{
	const struct sockaddr_in *dst_in4 =
		(const struct sockaddr_in *)dst_in;
	const struct sockaddr_in6 *dst_in6 =
		(const struct sockaddr_in6 *)dst_in;
	const void *daddr = (dst_in->sa_family == AF_INET) ?
		(const void *)&dst_in4->sin_addr.s_addr :
		(const void *)&dst_in6->sin6_addr;
	sa_family_t family = dst_in->sa_family;

	/* Gateway + ARPHRD_INFINIBAND -> IB router */
	if (has_gateway(dst, family) && dst->dev->type == ARPHRD_INFINIBAND)
		return ib_nl_fetch_ha(dst, dev_addr, daddr, seq, family);
	else
		return dst_fetch_ha(dst, dev_addr, daddr);
}