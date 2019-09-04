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
struct rdma_netdev {struct ipoib_dev_priv* clnt_priv; } ;
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int dummy; } ;

/* Variables and functions */
 struct rdma_netdev* netdev_priv (struct net_device const*) ; 

__attribute__((used)) static inline struct ipoib_dev_priv *ipoib_priv(const struct net_device *dev)
{
	struct rdma_netdev *rn = netdev_priv(dev);

	return rn->clnt_priv;
}