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
struct ieee_pfc {int /*<<< orphan*/  pfc_en; } ;
struct fm10k_intfc {int /*<<< orphan*/  pfc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_update_rx_drop_en (struct fm10k_intfc*) ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int fm10k_dcbnl_ieee_setpfc(struct net_device *dev, struct ieee_pfc *pfc)
{
	struct fm10k_intfc *interface = netdev_priv(dev);

	/* record PFC configuration to interface */
	interface->pfc_en = pfc->pfc_en;

	/* if we are running update the drop_en state for all queues */
	if (netif_running(dev))
		fm10k_update_rx_drop_en(interface);

	return 0;
}