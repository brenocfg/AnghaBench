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
struct net_device {int dummy; } ;
struct ice_pf {int dummy; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_2__ {struct ice_pf* back; } ;

/* Variables and functions */
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static inline struct ice_pf *ice_netdev_to_pf(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);

	return np->vsi->back;
}