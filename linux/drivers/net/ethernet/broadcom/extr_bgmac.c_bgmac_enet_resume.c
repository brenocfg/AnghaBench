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
 int /*<<< orphan*/  bgmac_chip_init (struct bgmac*) ; 
 int bgmac_dma_init (struct bgmac*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_attach (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_running (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_start_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_tx_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 

int bgmac_enet_resume(struct bgmac *bgmac)
{
	int rc;

	if (!netif_running(bgmac->net_dev))
		return 0;

	rc = bgmac_dma_init(bgmac);
	if (rc)
		return rc;

	bgmac_chip_init(bgmac);

	napi_enable(&bgmac->napi);

	netif_tx_lock(bgmac->net_dev);
	netif_device_attach(bgmac->net_dev);
	netif_tx_unlock(bgmac->net_dev);

	netif_start_queue(bgmac->net_dev);

	phy_start(bgmac->net_dev->phydev);

	return 0;
}