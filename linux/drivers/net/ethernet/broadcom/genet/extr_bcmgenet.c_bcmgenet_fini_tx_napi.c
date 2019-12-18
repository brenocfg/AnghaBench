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
struct bcmgenet_tx_ring {int /*<<< orphan*/  napi; } ;
struct bcmgenet_priv {struct bcmgenet_tx_ring* tx_rings; TYPE_1__* hw_params; } ;
struct TYPE_2__ {unsigned int tx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcmgenet_fini_tx_napi(struct bcmgenet_priv *priv)
{
	unsigned int i;
	struct bcmgenet_tx_ring *ring;

	for (i = 0; i < priv->hw_params->tx_queues; ++i) {
		ring = &priv->tx_rings[i];
		netif_napi_del(&ring->napi);
	}

	ring = &priv->tx_rings[DESC_INDEX];
	netif_napi_del(&ring->napi);
}