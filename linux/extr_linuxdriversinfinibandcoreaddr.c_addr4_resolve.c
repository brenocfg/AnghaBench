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
struct TYPE_4__ {void* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct TYPE_6__ {TYPE_2__* dev; } ;
struct rtable {TYPE_3__ dst; scalar_t__ rt_uses_gateway; } ;
struct rdma_dev_addr {int /*<<< orphan*/  hoplimit; int /*<<< orphan*/  network; int /*<<< orphan*/  net; int /*<<< orphan*/  bound_dev_if; } ;
struct flowi4 {void* saddr; int /*<<< orphan*/  flowi4_oif; void* daddr; } ;
typedef  int /*<<< orphan*/  fl4 ;
typedef  void* __be32 ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ARPHRD_INFINIBAND ; 
 int PTR_ERR_OR_ZERO (struct rtable*) ; 
 int /*<<< orphan*/  RDMA_NETWORK_IPV4 ; 
 int /*<<< orphan*/  ip4_dst_hoplimit (TYPE_3__*) ; 
 struct rtable* ip_route_output_key (int /*<<< orphan*/ ,struct flowi4*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int addr4_resolve(struct sockaddr_in *src_in,
			 const struct sockaddr_in *dst_in,
			 struct rdma_dev_addr *addr,
			 struct rtable **prt)
{
	__be32 src_ip = src_in->sin_addr.s_addr;
	__be32 dst_ip = dst_in->sin_addr.s_addr;
	struct rtable *rt;
	struct flowi4 fl4;
	int ret;

	memset(&fl4, 0, sizeof(fl4));
	fl4.daddr = dst_ip;
	fl4.saddr = src_ip;
	fl4.flowi4_oif = addr->bound_dev_if;
	rt = ip_route_output_key(addr->net, &fl4);
	ret = PTR_ERR_OR_ZERO(rt);
	if (ret)
		return ret;

	src_in->sin_family = AF_INET;
	src_in->sin_addr.s_addr = fl4.saddr;

	/* If there's a gateway and type of device not ARPHRD_INFINIBAND, we're
	 * definitely in RoCE v2 (as RoCE v1 isn't routable) set the network
	 * type accordingly.
	 */
	if (rt->rt_uses_gateway && rt->dst.dev->type != ARPHRD_INFINIBAND)
		addr->network = RDMA_NETWORK_IPV4;

	addr->hoplimit = ip4_dst_hoplimit(&rt->dst);

	*prt = rt;
	return 0;
}