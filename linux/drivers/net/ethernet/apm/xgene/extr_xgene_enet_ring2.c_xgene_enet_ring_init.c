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
typedef  int u64 ;
typedef  int u32 ;
struct xgene_enet_desc_ring {int* state; int dma; int id; int cfgsize; } ;

/* Variables and functions */
 int ACCEPTLERR ; 
 int QCOHERENT ; 
 int /*<<< orphan*/  RINGADDRH ; 
 int /*<<< orphan*/  RINGADDRL ; 
 int /*<<< orphan*/  RINGSIZE ; 
 int RING_BUFNUM_MASK ; 
 scalar_t__ RING_OWNER_CPU ; 
 int SET_BIT (int /*<<< orphan*/ ) ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X2_CFGCRID ; 
 int /*<<< orphan*/  X2_DEQINTEN ; 
 int /*<<< orphan*/  X2_INTLINE ; 
 int /*<<< orphan*/  X2_MSG_AM ; 
 int /*<<< orphan*/  X2_QBASE_AM ; 
 int /*<<< orphan*/  X2_SELTHRSH ; 
 scalar_t__ xgene_enet_ring_owner (int) ; 

__attribute__((used)) static void xgene_enet_ring_init(struct xgene_enet_desc_ring *ring)
{
	u32 *ring_cfg = ring->state;
	u64 addr = ring->dma;

	if (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU) {
		ring_cfg[0] |= SET_VAL(X2_INTLINE, ring->id & RING_BUFNUM_MASK);
		ring_cfg[3] |= SET_BIT(X2_DEQINTEN);
	}
	ring_cfg[0] |= SET_VAL(X2_CFGCRID, 2);

	addr >>= 8;
	ring_cfg[2] |= QCOHERENT | SET_VAL(RINGADDRL, addr);

	addr >>= 27;
	ring_cfg[3] |= SET_VAL(RINGSIZE, ring->cfgsize)
		    | ACCEPTLERR
		    | SET_VAL(RINGADDRH, addr);
	ring_cfg[4] |= SET_VAL(X2_SELTHRSH, 1);
	ring_cfg[5] |= SET_BIT(X2_QBASE_AM) | SET_BIT(X2_MSG_AM);
}