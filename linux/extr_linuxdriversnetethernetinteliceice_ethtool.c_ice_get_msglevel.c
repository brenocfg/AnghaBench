#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ debug_mask; } ;
struct ice_pf {int /*<<< orphan*/  msg_enable; TYPE_2__ hw; } ;
struct ice_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_3__ {struct ice_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 ice_get_msglevel(struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_pf *pf = np->vsi->back;

#ifndef CONFIG_DYNAMIC_DEBUG
	if (pf->hw.debug_mask)
		netdev_info(netdev, "hw debug_mask: 0x%llX\n",
			    pf->hw.debug_mask);
#endif /* !CONFIG_DYNAMIC_DEBUG */

	return pf->msg_enable;
}