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
struct net_device {int dummy; } ;
struct ib_device {struct net_device* (* alloc_rdma_netdev ) (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 scalar_t__ IS_ERR_OR_NULL (struct net_device*) ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 int /*<<< orphan*/  PTR_ERR (struct net_device*) ; 
 int /*<<< orphan*/  RDMA_NETDEV_IPOIB ; 
 struct net_device* ipoib_create_netdev_default (struct ib_device*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_setup_common ; 
 struct net_device* stub1 (struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *ipoib_get_netdev(struct ib_device *hca, u8 port,
					   const char *name)
{
	struct net_device *dev;

	if (hca->alloc_rdma_netdev) {
		dev = hca->alloc_rdma_netdev(hca, port,
					     RDMA_NETDEV_IPOIB, name,
					     NET_NAME_UNKNOWN,
					     ipoib_setup_common);
		if (IS_ERR_OR_NULL(dev) && PTR_ERR(dev) != -EOPNOTSUPP)
			return NULL;
	}

	if (!hca->alloc_rdma_netdev || PTR_ERR(dev) == -EOPNOTSUPP)
		dev = ipoib_create_netdev_default(hca, name, NET_NAME_UNKNOWN,
						  ipoib_setup_common);

	return dev;
}