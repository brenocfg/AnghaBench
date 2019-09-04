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
typedef  int u32 ;
struct xgene_enet_desc_ring {int* state; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int BUFPOOL_MODE ; 
 int CREATE_MASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RINGMODE_LEN ; 
 int RINGMODE_POS ; 
 int /*<<< orphan*/  RINGTYPE_LEN ; 
 int RINGTYPE_POS ; 
 int RING_BUFPOOL ; 
 int RING_REGULAR ; 
 int xgene_enet_is_bufpool (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_ring_set_type(struct xgene_enet_desc_ring *ring)
{
	u32 *ring_cfg = ring->state;
	bool is_bufpool;
	u32 val;

	is_bufpool = xgene_enet_is_bufpool(ring->id);
	val = (is_bufpool) ? RING_BUFPOOL : RING_REGULAR;
	ring_cfg[4] |= (val << RINGTYPE_POS) &
			CREATE_MASK(RINGTYPE_POS, RINGTYPE_LEN);

	if (is_bufpool) {
		ring_cfg[3] |= (BUFPOOL_MODE << RINGMODE_POS) &
				CREATE_MASK(RINGMODE_POS, RINGMODE_LEN);
	}
}