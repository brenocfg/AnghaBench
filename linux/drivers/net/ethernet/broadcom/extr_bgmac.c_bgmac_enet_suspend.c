#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bgmac {TYPE_1__* net_dev; int /*<<< orphan*/  napi; } ;
struct TYPE_6__ {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgmac_chip_intrs_off (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_chip_reset (struct bgmac*) ; 
 int /*<<< orphan*/  bgmac_dma_cleanup (struct bgmac*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

int bgmac_enet_suspend(struct bgmac *bgmac)
{
	if (!netif_running(bgmac->net_dev))
		return 0;

	phy_stop(bgmac->net_dev->phydev);

	netif_stop_queue(bgmac->net_dev);

	napi_disable(&bgmac->napi);

	netif_tx_lock(bgmac->net_dev);
	netif_device_detach(bgmac->net_dev);
	netif_tx_unlock(bgmac->net_dev);

	bgmac_chip_intrs_off(bgmac);
	bgmac_chip_reset(bgmac);
	bgmac_dma_cleanup(bgmac);

	return 0;
}