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
struct enetc_ndev_priv {int bdr_int_num; int num_rx_rings; int num_tx_rings; TYPE_1__* si; struct enetc_int_vector** int_vector; int /*<<< orphan*/ ** tx_ring; int /*<<< orphan*/ ** rx_ring; } ;
struct enetc_int_vector {int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct enetc_int_vector*) ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

void enetc_free_msix(struct enetc_ndev_priv *priv)
{
	int i;

	for (i = 0; i < priv->bdr_int_num; i++) {
		struct enetc_int_vector *v = priv->int_vector[i];

		netif_napi_del(&v->napi);
	}

	for (i = 0; i < priv->num_rx_rings; i++)
		priv->rx_ring[i] = NULL;

	for (i = 0; i < priv->num_tx_rings; i++)
		priv->tx_ring[i] = NULL;

	for (i = 0; i < priv->bdr_int_num; i++) {
		kfree(priv->int_vector[i]);
		priv->int_vector[i] = NULL;
	}

	/* disable all MSIX for this device */
	pci_free_irq_vectors(priv->si->pdev);
}