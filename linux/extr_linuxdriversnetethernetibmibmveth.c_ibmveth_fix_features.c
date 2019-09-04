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
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;

/* Variables and functions */
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_RXCSUM ; 

__attribute__((used)) static netdev_features_t ibmveth_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	/*
	 * Since the ibmveth firmware interface does not have the
	 * concept of separate tx/rx checksum offload enable, if rx
	 * checksum is disabled we also have to disable tx checksum
	 * offload. Once we disable rx checksum offload, we are no
	 * longer allowed to send tx buffers that are not properly
	 * checksummed.
	 */

	if (!(features & NETIF_F_RXCSUM))
		features &= ~NETIF_F_CSUM_MASK;

	return features;
}