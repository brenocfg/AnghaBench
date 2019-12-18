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
struct xlgmac_pdata {TYPE_1__* netdev; } ;
struct TYPE_2__ {int features; } ;

/* Variables and functions */
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  xlgmac_disable_rx_csum (struct xlgmac_pdata*) ; 
 int /*<<< orphan*/  xlgmac_enable_rx_csum (struct xlgmac_pdata*) ; 

__attribute__((used)) static void xlgmac_config_checksum_offload(struct xlgmac_pdata *pdata)
{
	if (pdata->netdev->features & NETIF_F_RXCSUM)
		xlgmac_enable_rx_csum(pdata);
	else
		xlgmac_disable_rx_csum(pdata);
}