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
typedef  size_t u32 ;
struct xgene_enet_desc_ring {size_t slots; int id; int irq_mbox_dma; int /*<<< orphan*/ * raw_desc; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t CSR_VMID0_INTR_MBOX ; 
 int RING_BUFNUM_MASK ; 
 scalar_t__ RING_OWNER_CPU ; 
 int /*<<< orphan*/  xgene_enet_clr_ring_state (struct xgene_enet_desc_ring*) ; 
 size_t xgene_enet_get_numslots (int,int /*<<< orphan*/ ) ; 
 int xgene_enet_is_bufpool (int) ; 
 int /*<<< orphan*/  xgene_enet_mark_desc_slot_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ xgene_enet_ring_owner (int) ; 
 int /*<<< orphan*/  xgene_enet_ring_wr32 (struct xgene_enet_desc_ring*,size_t,int) ; 
 int /*<<< orphan*/  xgene_enet_set_ring_id (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_set_ring_state (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static struct xgene_enet_desc_ring *xgene_enet_setup_ring(
				    struct xgene_enet_desc_ring *ring)
{
	bool is_bufpool;
	u32 addr, i;

	xgene_enet_clr_ring_state(ring);
	xgene_enet_set_ring_state(ring);
	xgene_enet_set_ring_id(ring);

	ring->slots = xgene_enet_get_numslots(ring->id, ring->size);

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	if (is_bufpool || xgene_enet_ring_owner(ring->id) != RING_OWNER_CPU)
		return ring;

	addr = CSR_VMID0_INTR_MBOX + (4 * (ring->id & RING_BUFNUM_MASK));
	xgene_enet_ring_wr32(ring, addr, ring->irq_mbox_dma >> 10);

	for (i = 0; i < ring->slots; i++)
		xgene_enet_mark_desc_slot_empty(&ring->raw_desc[i]);

	return ring;
}