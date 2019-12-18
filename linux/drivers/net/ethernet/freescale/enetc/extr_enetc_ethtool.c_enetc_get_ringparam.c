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
typedef  scalar_t__ u32 ;
struct net_device {int dummy; } ;
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct enetc_ndev_priv {scalar_t__ rx_bd_count; scalar_t__ tx_bd_count; TYPE_1__* si; } ;
struct enetc_hw {int dummy; } ;
struct TYPE_2__ {struct enetc_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_RBLENR ; 
 int /*<<< orphan*/  ENETC_TBLENR ; 
 scalar_t__ enetc_rxbdr_rd (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ enetc_txbdr_rd (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enetc_ndev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct enetc_ndev_priv*,struct enetc_hw*,struct net_device*,char*,scalar_t__) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static void enetc_get_ringparam(struct net_device *ndev,
				struct ethtool_ringparam *ring)
{
	struct enetc_ndev_priv *priv = netdev_priv(ndev);

	ring->rx_pending = priv->rx_bd_count;
	ring->tx_pending = priv->tx_bd_count;

	/* do some h/w sanity checks for BDR length */
	if (netif_running(ndev)) {
		struct enetc_hw *hw = &priv->si->hw;
		u32 val = enetc_rxbdr_rd(hw, 0, ENETC_RBLENR);

		if (val != priv->rx_bd_count)
			netif_err(priv, hw, ndev, "RxBDR[RBLENR] = %d!\n", val);

		val = enetc_txbdr_rd(hw, 0, ENETC_TBLENR);

		if (val != priv->tx_bd_count)
			netif_err(priv, hw, ndev, "TxBDR[TBLENR] = %d!\n", val);
	}
}