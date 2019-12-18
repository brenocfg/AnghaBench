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
struct enetc_ndev_priv {int num_tx_rings; int /*<<< orphan*/ * tx_ring; } ;

/* Variables and functions */
 int enetc_alloc_txbdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_free_txbdr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_alloc_tx_resources(struct enetc_ndev_priv *priv)
{
	int i, err;

	for (i = 0; i < priv->num_tx_rings; i++) {
		err = enetc_alloc_txbdr(priv->tx_ring[i]);

		if (err)
			goto fail;
	}

	return 0;

fail:
	while (i-- > 0)
		enetc_free_txbdr(priv->tx_ring[i]);

	return err;
}