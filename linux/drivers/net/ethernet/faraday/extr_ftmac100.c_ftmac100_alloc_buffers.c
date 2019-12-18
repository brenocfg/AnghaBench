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
struct ftmac100_rxdes {int dummy; } ;
struct ftmac100_descs {int dummy; } ;
struct ftmac100 {TYPE_1__* descs; int /*<<< orphan*/  descs_dma_addr; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * txdes; struct ftmac100_rxdes* rxdes; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int RX_QUEUE_ENTRIES ; 
 int TX_QUEUE_ENTRIES ; 
 TYPE_1__* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ftmac100_alloc_rx_page (struct ftmac100*,struct ftmac100_rxdes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftmac100_free_buffers (struct ftmac100*) ; 
 int /*<<< orphan*/  ftmac100_rxdes_set_end_of_ring (struct ftmac100_rxdes*) ; 
 int /*<<< orphan*/  ftmac100_txdes_set_end_of_ring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftmac100_alloc_buffers(struct ftmac100 *priv)
{
	int i;

	priv->descs = dma_alloc_coherent(priv->dev,
					 sizeof(struct ftmac100_descs),
					 &priv->descs_dma_addr, GFP_KERNEL);
	if (!priv->descs)
		return -ENOMEM;

	/* initialize RX ring */
	ftmac100_rxdes_set_end_of_ring(&priv->descs->rxdes[RX_QUEUE_ENTRIES - 1]);

	for (i = 0; i < RX_QUEUE_ENTRIES; i++) {
		struct ftmac100_rxdes *rxdes = &priv->descs->rxdes[i];

		if (ftmac100_alloc_rx_page(priv, rxdes, GFP_KERNEL))
			goto err;
	}

	/* initialize TX ring */
	ftmac100_txdes_set_end_of_ring(&priv->descs->txdes[TX_QUEUE_ENTRIES - 1]);
	return 0;

err:
	ftmac100_free_buffers(priv);
	return -ENOMEM;
}