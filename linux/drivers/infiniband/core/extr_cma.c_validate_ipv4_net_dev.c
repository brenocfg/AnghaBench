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
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct flowi4 {void* saddr; void* daddr; int /*<<< orphan*/  flowi4_iif; } ;
struct fib_result {int dummy; } ;
typedef  int /*<<< orphan*/  fl4 ;
typedef  void* __be32 ;

/* Variables and functions */
 struct net_device* FIB_RES_DEV (struct fib_result) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int fib_lookup (int /*<<< orphan*/ ,struct flowi4*,struct fib_result*,int /*<<< orphan*/ ) ; 
 scalar_t__ ipv4_is_lbcast (void*) ; 
 scalar_t__ ipv4_is_loopback (void*) ; 
 scalar_t__ ipv4_is_multicast (void*) ; 
 scalar_t__ ipv4_is_zeronet (void*) ; 
 int /*<<< orphan*/  memset (struct flowi4*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static bool validate_ipv4_net_dev(struct net_device *net_dev,
				  const struct sockaddr_in *dst_addr,
				  const struct sockaddr_in *src_addr)
{
	__be32 daddr = dst_addr->sin_addr.s_addr,
	       saddr = src_addr->sin_addr.s_addr;
	struct fib_result res;
	struct flowi4 fl4;
	int err;
	bool ret;

	if (ipv4_is_multicast(saddr) || ipv4_is_lbcast(saddr) ||
	    ipv4_is_lbcast(daddr) || ipv4_is_zeronet(saddr) ||
	    ipv4_is_zeronet(daddr) || ipv4_is_loopback(daddr) ||
	    ipv4_is_loopback(saddr))
		return false;

	memset(&fl4, 0, sizeof(fl4));
	fl4.flowi4_iif = net_dev->ifindex;
	fl4.daddr = daddr;
	fl4.saddr = saddr;

	rcu_read_lock();
	err = fib_lookup(dev_net(net_dev), &fl4, &res, 0);
	ret = err == 0 && FIB_RES_DEV(res) == net_dev;
	rcu_read_unlock();

	return ret;
}