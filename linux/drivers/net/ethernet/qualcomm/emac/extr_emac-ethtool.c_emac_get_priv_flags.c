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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct emac_adapter {scalar_t__ single_pause_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_PRIV_ENABLE_SINGLE_PAUSE ; 
 struct emac_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 emac_get_priv_flags(struct net_device *netdev)
{
	struct emac_adapter *adpt = netdev_priv(netdev);

	return adpt->single_pause_mode ? EMAC_PRIV_ENABLE_SINGLE_PAUSE : 0;
}