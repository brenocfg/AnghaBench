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
struct ethtool_wolinfo {int supported; int wolopts; } ;
struct atl1e_adapter {int wol; } ;

/* Variables and functions */
 int AT_WUFC_BC ; 
 int AT_WUFC_EX ; 
 int AT_WUFC_LNKC ; 
 int AT_WUFC_MAG ; 
 int AT_WUFC_MC ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 
 struct atl1e_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void atl1e_get_wol(struct net_device *netdev,
			  struct ethtool_wolinfo *wol)
{
	struct atl1e_adapter *adapter = netdev_priv(netdev);

	wol->supported = WAKE_MAGIC | WAKE_PHY;
	wol->wolopts = 0;

	if (adapter->wol & AT_WUFC_EX)
		wol->wolopts |= WAKE_UCAST;
	if (adapter->wol & AT_WUFC_MC)
		wol->wolopts |= WAKE_MCAST;
	if (adapter->wol & AT_WUFC_BC)
		wol->wolopts |= WAKE_BCAST;
	if (adapter->wol & AT_WUFC_MAG)
		wol->wolopts |= WAKE_MAGIC;
	if (adapter->wol & AT_WUFC_LNKC)
		wol->wolopts |= WAKE_PHY;
}