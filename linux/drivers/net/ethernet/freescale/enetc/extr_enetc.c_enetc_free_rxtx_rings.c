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
struct enetc_ndev_priv {int num_rx_rings; int num_tx_rings; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  enetc_free_rx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_free_tx_ring (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enetc_free_rxtx_rings(struct enetc_ndev_priv *priv)
{
	int i;

	for (i = 0; i < priv->num_rx_rings; i++)
		enetc_free_rx_ring(priv->rx_ring[i]);

	for (i = 0; i < priv->num_tx_rings; i++)
		enetc_free_tx_ring(priv->tx_ring[i]);
}