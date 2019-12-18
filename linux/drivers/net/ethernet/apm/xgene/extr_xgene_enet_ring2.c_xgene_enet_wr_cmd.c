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
struct xgene_enet_desc_ring {int id; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int INTR_CLEAR ; 
 int RING_BUFNUM_MASK ; 
 scalar_t__ RING_OWNER_CPU ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X2_INTLINE ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 scalar_t__ xgene_enet_ring_owner (int) ; 

__attribute__((used)) static void xgene_enet_wr_cmd(struct xgene_enet_desc_ring *ring, int count)
{
	u32 data = 0;

	if (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU) {
		data = SET_VAL(X2_INTLINE, ring->id & RING_BUFNUM_MASK) |
		       INTR_CLEAR;
	}
	data |= (count & GENMASK(16, 0));

	iowrite32(data, ring->cmd);
}