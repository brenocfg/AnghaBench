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
struct enetc_ndev_priv {int num_rx_rings; int num_tx_rings; TYPE_1__* si; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_RBIER ; 
 int /*<<< orphan*/  ENETC_RBIER_RXTIE ; 
 int /*<<< orphan*/  ENETC_TBIER ; 
 int /*<<< orphan*/  ENETC_TBIER_TXTIE ; 
 int /*<<< orphan*/  enetc_rxbdr_wr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_txbdr_wr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_enable_interrupts(struct enetc_ndev_priv *priv)
{
	int i;

	/* enable Tx & Rx event indication */
	for (i = 0; i < priv->num_rx_rings; i++) {
		enetc_rxbdr_wr(&priv->si->hw, i,
			       ENETC_RBIER, ENETC_RBIER_RXTIE);
	}

	for (i = 0; i < priv->num_tx_rings; i++) {
		enetc_txbdr_wr(&priv->si->hw, i,
			       ENETC_TBIER, ENETC_TBIER_TXTIE);
	}
}