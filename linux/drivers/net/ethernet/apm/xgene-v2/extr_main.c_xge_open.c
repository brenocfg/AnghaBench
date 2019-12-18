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
struct xge_pdata {int /*<<< orphan*/  napi; } ;
struct net_device {int /*<<< orphan*/  phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMARXCTRL ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_start (int /*<<< orphan*/ ) ; 
 int xge_create_desc_rings (struct net_device*) ; 
 int /*<<< orphan*/  xge_intr_enable (struct xge_pdata*) ; 
 int /*<<< orphan*/  xge_mac_enable (struct xge_pdata*) ; 
 int xge_request_irq (struct net_device*) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xge_open(struct net_device *ndev)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	int ret;

	ret = xge_create_desc_rings(ndev);
	if (ret)
		return ret;

	napi_enable(&pdata->napi);
	ret = xge_request_irq(ndev);
	if (ret)
		return ret;

	xge_intr_enable(pdata);
	xge_wr_csr(pdata, DMARXCTRL, 1);

	phy_start(ndev->phydev);
	xge_mac_enable(pdata);
	netif_start_queue(ndev);

	return 0;
}