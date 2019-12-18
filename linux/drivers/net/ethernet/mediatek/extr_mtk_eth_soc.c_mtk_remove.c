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
struct platform_device {int dummy; } ;
struct mtk_mac {int /*<<< orphan*/  phylink; } ;
struct mtk_eth {int /*<<< orphan*/  rx_napi; int /*<<< orphan*/  tx_napi; int /*<<< orphan*/ * netdev; } ;

/* Variables and functions */
 int MTK_MAC_COUNT ; 
 int /*<<< orphan*/  mtk_cleanup (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_hw_deinit (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_mdio_cleanup (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_stop (int /*<<< orphan*/ ) ; 
 struct mtk_mac* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_disconnect_phy (int /*<<< orphan*/ ) ; 
 struct mtk_eth* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mtk_remove(struct platform_device *pdev)
{
	struct mtk_eth *eth = platform_get_drvdata(pdev);
	struct mtk_mac *mac;
	int i;

	/* stop all devices to make sure that dma is properly shut down */
	for (i = 0; i < MTK_MAC_COUNT; i++) {
		if (!eth->netdev[i])
			continue;
		mtk_stop(eth->netdev[i]);
		mac = netdev_priv(eth->netdev[i]);
		phylink_disconnect_phy(mac->phylink);
	}

	mtk_hw_deinit(eth);

	netif_napi_del(&eth->tx_napi);
	netif_napi_del(&eth->rx_napi);
	mtk_cleanup(eth);
	mtk_mdio_cleanup(eth);

	return 0;
}