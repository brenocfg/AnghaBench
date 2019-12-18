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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ debug_mask; } ;
struct i40e_pf {scalar_t__ msg_enable; TYPE_2__ hw; } ;
struct i40e_netdev_priv {TYPE_1__* vsi; } ;
struct TYPE_3__ {struct i40e_pf* back; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,scalar_t__) ; 
 struct i40e_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 i40e_get_msglevel(struct net_device *netdev)
{
	struct i40e_netdev_priv *np = netdev_priv(netdev);
	struct i40e_pf *pf = np->vsi->back;
	u32 debug_mask = pf->hw.debug_mask;

	if (debug_mask)
		netdev_info(netdev, "i40e debug_mask: 0x%08X\n", debug_mask);

	return pf->msg_enable;
}