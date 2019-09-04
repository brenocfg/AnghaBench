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
struct xgbe_hw_if {int /*<<< orphan*/  (* set_mac_address ) (struct xgbe_prv_data*,int /*<<< orphan*/ ) ;} ;
struct xgbe_prv_data {struct xgbe_hw_if hw_if; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_set_mac_address(struct net_device *netdev, void *addr)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct sockaddr *saddr = addr;

	DBGPR("-->xgbe_set_mac_address\n");

	if (!is_valid_ether_addr(saddr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(netdev->dev_addr, saddr->sa_data, netdev->addr_len);

	hw_if->set_mac_address(pdata, netdev->dev_addr);

	DBGPR("<--xgbe_set_mac_address\n");

	return 0;
}