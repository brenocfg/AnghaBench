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
struct net_device {int features; int hw_features; } ;
struct ef4_nic {struct net_device* net_dev; } ;
typedef  int netdev_features_t ;

/* Variables and functions */

__attribute__((used)) static inline netdev_features_t ef4_supported_features(const struct ef4_nic *efx)
{
	const struct net_device *net_dev = efx->net_dev;

	return net_dev->features | net_dev->hw_features;
}