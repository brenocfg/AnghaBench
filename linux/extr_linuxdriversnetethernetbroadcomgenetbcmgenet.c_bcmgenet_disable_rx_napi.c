#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct TYPE_5__ {TYPE_1__ dim; } ;
struct bcmgenet_rx_ring {TYPE_2__ dim; int /*<<< orphan*/  napi; } ;
struct bcmgenet_priv {struct bcmgenet_rx_ring* rx_rings; TYPE_3__* hw_params; } ;
struct TYPE_6__ {unsigned int rx_queues; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcmgenet_disable_rx_napi(struct bcmgenet_priv *priv)
{
	unsigned int i;
	struct bcmgenet_rx_ring *ring;

	for (i = 0; i < priv->hw_params->rx_queues; ++i) {
		ring = &priv->rx_rings[i];
		napi_disable(&ring->napi);
		cancel_work_sync(&ring->dim.dim.work);
	}

	ring = &priv->rx_rings[DESC_INDEX];
	napi_disable(&ring->napi);
	cancel_work_sync(&ring->dim.dim.work);
}