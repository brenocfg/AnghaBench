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
struct xgene_enet_desc_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_PBM_COAL ; 
 int /*<<< orphan*/  CSR_PBM_CTICK0 ; 
 int /*<<< orphan*/  CSR_PBM_CTICK1 ; 
 int /*<<< orphan*/  CSR_PBM_CTICK2 ; 
 int /*<<< orphan*/  CSR_PBM_CTICK3 ; 
 int /*<<< orphan*/  CSR_THRESHOLD0_SET1 ; 
 int /*<<< orphan*/  CSR_THRESHOLD1_SET1 ; 
 int /*<<< orphan*/  xgene_enet_ring_wr32 (struct xgene_enet_desc_ring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_enet_setup_coalescing(struct xgene_enet_desc_ring *ring)
{
	u32 data = 0x77777777;

	xgene_enet_ring_wr32(ring, CSR_PBM_COAL, 0x8e);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK0, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK1, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK2, data);
	xgene_enet_ring_wr32(ring, CSR_PBM_CTICK3, data);
	xgene_enet_ring_wr32(ring, CSR_THRESHOLD0_SET1, 0x08);
	xgene_enet_ring_wr32(ring, CSR_THRESHOLD1_SET1, 0x10);
}