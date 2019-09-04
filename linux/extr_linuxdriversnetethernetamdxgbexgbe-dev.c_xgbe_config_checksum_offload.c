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
struct xgbe_prv_data {TYPE_1__* netdev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  xgbe_disable_rx_csum (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_enable_rx_csum (struct xgbe_prv_data*) ; 

__attribute__((used)) static void xgbe_config_checksum_offload(struct xgbe_prv_data *pdata)
{
	if (pdata->netdev->features & NETIF_F_RXCSUM)
		xgbe_enable_rx_csum(pdata);
	else
		xgbe_disable_rx_csum(pdata);
}