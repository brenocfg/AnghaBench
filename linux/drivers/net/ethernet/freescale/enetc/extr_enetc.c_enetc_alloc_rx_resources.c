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
struct enetc_ndev_priv {int num_rx_rings; int /*<<< orphan*/ * rx_ring; } ;

/* Variables and functions */
 int enetc_alloc_rxbdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_free_rxbdr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_alloc_rx_resources(struct enetc_ndev_priv *priv)
{
	int i, err;

	for (i = 0; i < priv->num_rx_rings; i++) {
		err = enetc_alloc_rxbdr(priv->rx_ring[i]);

		if (err)
			goto fail;
	}

	return 0;

fail:
	while (i-- > 0)
		enetc_free_rxbdr(priv->rx_ring[i]);

	return err;
}