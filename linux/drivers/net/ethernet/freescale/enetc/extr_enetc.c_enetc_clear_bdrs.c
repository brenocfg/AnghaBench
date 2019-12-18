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
struct enetc_ndev_priv {int num_tx_rings; int num_rx_rings; int /*<<< orphan*/ * rx_ring; TYPE_1__* si; int /*<<< orphan*/ * tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_clear_rxbdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_clear_txbdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void enetc_clear_bdrs(struct enetc_ndev_priv *priv)
{
	int i;

	for (i = 0; i < priv->num_tx_rings; i++)
		enetc_clear_txbdr(&priv->si->hw, priv->tx_ring[i]);

	for (i = 0; i < priv->num_rx_rings; i++)
		enetc_clear_rxbdr(&priv->si->hw, priv->rx_ring[i]);

	udelay(1);
}