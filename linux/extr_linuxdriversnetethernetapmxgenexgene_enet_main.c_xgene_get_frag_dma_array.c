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
struct xgene_enet_desc_ring {size_t tail; TYPE_1__* cp_ring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/ * frag_dma_addr; } ;

/* Variables and functions */
 size_t MAX_SKB_FRAGS ; 

__attribute__((used)) static dma_addr_t *xgene_get_frag_dma_array(struct xgene_enet_desc_ring *ring)
{
	return &ring->cp_ring->frag_dma_addr[ring->tail * MAX_SKB_FRAGS];
}