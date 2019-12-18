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
typedef  int /*<<< orphan*/  u32 ;
struct sockaddr {int dummy; } ;
struct rdma_dev_addr {int /*<<< orphan*/  src_dev_addr; int /*<<< orphan*/  dst_dev_addr; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 unsigned int IFF_LOOPBACK ; 
 unsigned int IFF_NOARP ; 
 int /*<<< orphan*/  MAX_ADDR_LEN ; 
 int fetch_ha (struct dst_entry const*,struct rdma_dev_addr*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int addr_resolve_neigh(const struct dst_entry *dst,
			      const struct sockaddr *dst_in,
			      struct rdma_dev_addr *addr,
			      unsigned int ndev_flags,
			      u32 seq)
{
	int ret = 0;

	if (ndev_flags & IFF_LOOPBACK) {
		memcpy(addr->dst_dev_addr, addr->src_dev_addr, MAX_ADDR_LEN);
	} else {
		if (!(ndev_flags & IFF_NOARP)) {
			/* If the device doesn't do ARP internally */
			ret = fetch_ha(dst, addr, dst_in, seq);
		}
	}
	return ret;
}