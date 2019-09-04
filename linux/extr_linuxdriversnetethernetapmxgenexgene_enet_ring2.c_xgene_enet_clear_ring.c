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
struct xgene_enet_desc_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xgene_enet_clr_desc_ring_id (struct xgene_enet_desc_ring*) ; 
 int /*<<< orphan*/  xgene_enet_clr_ring_state (struct xgene_enet_desc_ring*) ; 

__attribute__((used)) static void xgene_enet_clear_ring(struct xgene_enet_desc_ring *ring)
{
	xgene_enet_clr_desc_ring_id(ring);
	xgene_enet_clr_ring_state(ring);
}