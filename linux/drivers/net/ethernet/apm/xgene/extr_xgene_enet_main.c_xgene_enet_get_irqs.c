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
struct xgene_enet_pdata {scalar_t__ phy_mode; int rxq_cnt; int txq_cnt; int cq_cnt; int* irqs; struct platform_device* pdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int XGENE_MAX_ENET_IRQ ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static int xgene_enet_get_irqs(struct xgene_enet_pdata *pdata)
{
	struct platform_device *pdev = pdata->pdev;
	int i, ret, max_irqs;

	if (phy_interface_mode_is_rgmii(pdata->phy_mode))
		max_irqs = 1;
	else if (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII)
		max_irqs = 2;
	else
		max_irqs = XGENE_MAX_ENET_IRQ;

	for (i = 0; i < max_irqs; i++) {
		ret = platform_get_irq(pdev, i);
		if (ret <= 0) {
			if (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) {
				max_irqs = i;
				pdata->rxq_cnt = max_irqs / 2;
				pdata->txq_cnt = max_irqs / 2;
				pdata->cq_cnt = max_irqs / 2;
				break;
			}
			return ret ? : -ENXIO;
		}
		pdata->irqs[i] = ret;
	}

	return 0;
}