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
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr {int dummy; } ;
struct rdma_dev_addr {int /*<<< orphan*/  src_dev_addr; int /*<<< orphan*/  dst_dev_addr; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int IFF_LOOPBACK ; 
 int IFF_NOARP ; 
 int /*<<< orphan*/  MAX_ADDR_LEN ; 
 int fetch_ha (struct dst_entry const*,struct rdma_dev_addr*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_copy_addr (struct rdma_dev_addr*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int rdma_translate_ip (struct sockaddr const*,struct rdma_dev_addr*) ; 

__attribute__((used)) static int addr_resolve_neigh(const struct dst_entry *dst,
			      const struct sockaddr *dst_in,
			      struct rdma_dev_addr *addr,
			      u32 seq)
{
	if (dst->dev->flags & IFF_LOOPBACK) {
		int ret;

		ret = rdma_translate_ip(dst_in, addr);
		if (!ret)
			memcpy(addr->dst_dev_addr, addr->src_dev_addr,
			       MAX_ADDR_LEN);

		return ret;
	}

	/* If the device doesn't do ARP internally */
	if (!(dst->dev->flags & IFF_NOARP))
		return fetch_ha(dst, addr, dst_in, seq);

	rdma_copy_addr(addr, dst->dev, NULL);

	return 0;
}