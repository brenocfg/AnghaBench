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
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_net_netdev_ops ; 

__attribute__((used)) static inline bool nfp_netdev_is_nfp_net(struct net_device *netdev)
{
	return netdev->netdev_ops == &nfp_net_netdev_ops;
}