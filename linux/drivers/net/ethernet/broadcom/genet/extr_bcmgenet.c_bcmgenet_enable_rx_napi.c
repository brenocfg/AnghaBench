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
struct bcmgenet_rx_ring {int /*<<< orphan*/  (* int_enable ) (struct bcmgenet_rx_ring*) ;int /*<<< orphan*/  napi; } ;
struct bcmgenet_priv {struct bcmgenet_rx_ring* rx_rings; TYPE_1__* hw_params; } ;
struct TYPE_2__ {unsigned int rx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bcmgenet_rx_ring*) ; 
 int /*<<< orphan*/  stub2 (struct bcmgenet_rx_ring*) ; 

__attribute__((used)) static void bcmgenet_enable_rx_napi(struct bcmgenet_priv *priv)
{
	unsigned int i;
	struct bcmgenet_rx_ring *ring;

	for (i = 0; i < priv->hw_params->rx_queues; ++i) {
		ring = &priv->rx_rings[i];
		napi_enable(&ring->napi);
		ring->int_enable(ring);
	}

	ring = &priv->rx_rings[DESC_INDEX];
	napi_enable(&ring->napi);
	ring->int_enable(ring);
}