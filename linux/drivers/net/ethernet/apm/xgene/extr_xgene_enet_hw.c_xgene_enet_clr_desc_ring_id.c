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
struct xgene_enet_desc_ring {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_RING_ID ; 
 int /*<<< orphan*/  CSR_RING_ID_BUF ; 
 int OVERWRITE ; 
 int /*<<< orphan*/  xgene_enet_ring_wr32 (struct xgene_enet_desc_ring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_enet_clr_desc_ring_id(struct xgene_enet_desc_ring *ring)
{
	u32 ring_id;

	ring_id = ring->id | OVERWRITE;
	xgene_enet_ring_wr32(ring, CSR_RING_ID, ring_id);
	xgene_enet_ring_wr32(ring, CSR_RING_ID_BUF, 0);
}