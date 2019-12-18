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
struct xgbe_hw_if {int /*<<< orphan*/  (* config_rx_mode ) (struct xgbe_prv_data*) ;} ;
struct xgbe_prv_data {struct xgbe_hw_if hw_if; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_set_rx_mode(struct net_device *netdev)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;

	DBGPR("-->xgbe_set_rx_mode\n");

	hw_if->config_rx_mode(pdata);

	DBGPR("<--xgbe_set_rx_mode\n");
}