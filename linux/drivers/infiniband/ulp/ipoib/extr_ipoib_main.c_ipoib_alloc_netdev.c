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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_netdev {int dummy; } ;
struct net_device {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct net_device*) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  RDMA_NETDEV_IPOIB ; 
 struct net_device* alloc_netdev (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_setup_common ; 
 struct net_device* rdma_alloc_netdev (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *ipoib_alloc_netdev(struct ib_device *hca, u8 port,
					     const char *name)
{
	struct net_device *dev;

	dev = rdma_alloc_netdev(hca, port, RDMA_NETDEV_IPOIB, name,
				NET_NAME_UNKNOWN, ipoib_setup_common);
	if (!IS_ERR(dev) || PTR_ERR(dev) != -EOPNOTSUPP)
		return dev;

	dev = alloc_netdev(sizeof(struct rdma_netdev), name, NET_NAME_UNKNOWN,
			   ipoib_setup_common);
	if (!dev)
		return ERR_PTR(-ENOMEM);
	return dev;
}