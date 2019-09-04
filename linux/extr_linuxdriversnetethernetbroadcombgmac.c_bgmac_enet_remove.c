#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bgmac {TYPE_1__* net_dev; int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_dma_free (struct bgmac*) ; 
 int /*<<< orphan*/  free_netdev (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (TYPE_1__*) ; 

void bgmac_enet_remove(struct bgmac *bgmac)
{
	unregister_netdev(bgmac->net_dev);
	phy_disconnect(bgmac->net_dev->phydev);
	netif_napi_del(&bgmac->napi);
	bgmac_dma_free(bgmac);
	free_netdev(bgmac->net_dev);
}