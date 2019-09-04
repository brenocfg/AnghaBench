#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mvneta_rx_queue {int size; int last_desc; int /*<<< orphan*/  descs; int /*<<< orphan*/  descs_phys; } ;
struct mvneta_port {int rx_ring_size; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MVNETA_DESC_ALIGNED_SIZE ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvneta_rxq_sw_init(struct mvneta_port *pp,
			      struct mvneta_rx_queue *rxq)
{
	rxq->size = pp->rx_ring_size;

	/* Allocate memory for RX descriptors */
	rxq->descs = dma_alloc_coherent(pp->dev->dev.parent,
					rxq->size * MVNETA_DESC_ALIGNED_SIZE,
					&rxq->descs_phys, GFP_KERNEL);
	if (!rxq->descs)
		return -ENOMEM;

	rxq->last_desc = rxq->size - 1;

	return 0;
}