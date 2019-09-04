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
struct xgene_enet_desc_ring {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ RING_OWNER_ETH0 ; 
 scalar_t__ RING_OWNER_ETH1 ; 
 int /*<<< orphan*/  xgene_enet_ring_init (struct xgene_enet_desc_ring*) ; 
 scalar_t__ xgene_enet_ring_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_ring_set_recombbuf (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_ring_set_type (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_write_ring_state (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static void xgene_enet_set_ring_state(struct xgene_enet_desc_ring *ring)
{
	xgene_enet_ring_set_type(ring);

	if (xgene_enet_ring_owner(ring->id) == RING_OWNER_ETH0 ||
	    xgene_enet_ring_owner(ring->id) == RING_OWNER_ETH1)
		xgene_enet_ring_set_recombbuf(ring);

	xgene_enet_ring_init(ring);
	xgene_enet_write_ring_state(ring);
}