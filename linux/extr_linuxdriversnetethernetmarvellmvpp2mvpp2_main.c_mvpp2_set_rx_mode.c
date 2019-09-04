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
struct net_device {int flags; int /*<<< orphan*/  mc; int /*<<< orphan*/  uc; } ;
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MVPP2_PRS_L2_MULTI_CAST ; 
 int /*<<< orphan*/  MVPP2_PRS_L2_UNI_CAST ; 
 scalar_t__ MVPP2_PRS_MAC_MC_FILT_MAX ; 
 scalar_t__ MVPP2_PRS_MAC_UC_FILT_MAX ; 
 scalar_t__ mvpp2_prs_mac_da_accept_list (struct mvpp2_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_prs_mac_del_all (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_prs_mac_promisc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvpp2_set_rx_promisc (struct mvpp2_port*,int) ; 
 scalar_t__ netdev_mc_count (struct net_device*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netdev_uc_count (struct net_device*) ; 

__attribute__((used)) static void mvpp2_set_rx_mode(struct net_device *dev)
{
	struct mvpp2_port *port = netdev_priv(dev);

	/* Clear the whole UC and MC list */
	mvpp2_prs_mac_del_all(port);

	if (dev->flags & IFF_PROMISC) {
		mvpp2_set_rx_promisc(port, true);
		return;
	}

	mvpp2_set_rx_promisc(port, false);

	if (netdev_uc_count(dev) > MVPP2_PRS_MAC_UC_FILT_MAX ||
	    mvpp2_prs_mac_da_accept_list(port, &dev->uc))
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_UNI_CAST, true);

	if (dev->flags & IFF_ALLMULTI) {
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_MULTI_CAST, true);
		return;
	}

	if (netdev_mc_count(dev) > MVPP2_PRS_MAC_MC_FILT_MAX ||
	    mvpp2_prs_mac_da_accept_list(port, &dev->mc))
		mvpp2_prs_mac_promisc_set(port->priv, port->id,
					  MVPP2_PRS_L2_MULTI_CAST, true);
}