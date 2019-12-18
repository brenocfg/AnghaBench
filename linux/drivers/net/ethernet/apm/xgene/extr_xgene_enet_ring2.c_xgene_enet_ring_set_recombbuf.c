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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_enet_desc_ring {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RECOMBBUF ; 
 int /*<<< orphan*/  SET_VAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  X2_RECOMTIMEOUT ; 

__attribute__((used)) static void xgene_enet_ring_set_recombbuf(struct xgene_enet_desc_ring *ring)
{
	u32 *ring_cfg = ring->state;

	ring_cfg[3] |= RECOMBBUF;
	ring_cfg[4] |= SET_VAL(X2_RECOMTIMEOUT, 0x7);
}