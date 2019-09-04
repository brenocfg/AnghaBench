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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct arc_emac_priv {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int EN_MASK ; 
 int ERR_MASK ; 
 int RXINT_MASK ; 
 int /*<<< orphan*/  R_CTRL ; 
 int /*<<< orphan*/  R_ENABLE ; 
 int TXINT_MASK ; 
 int /*<<< orphan*/  arc_free_rx_queue (struct net_device*) ; 
 int /*<<< orphan*/  arc_free_tx_queue (struct net_device*) ; 
 int /*<<< orphan*/  arc_reg_clr (struct arc_emac_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct arc_emac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arc_emac_stop(struct net_device *ndev)
{
	struct arc_emac_priv *priv = netdev_priv(ndev);

	napi_disable(&priv->napi);
	netif_stop_queue(ndev);

	phy_stop(ndev->phydev);

	/* Disable interrupts */
	arc_reg_clr(priv, R_ENABLE, RXINT_MASK | TXINT_MASK | ERR_MASK);

	/* Disable EMAC */
	arc_reg_clr(priv, R_CTRL, EN_MASK);

	/* Return the sk_buff to system */
	arc_free_tx_queue(ndev);
	arc_free_rx_queue(ndev);

	return 0;
}