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
struct xgene_enet_pdata {scalar_t__ enet_id; } ;
struct xgene_enet_desc_ring {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ RING_OWNER_CPU ; 
 scalar_t__ XGENE_ENET2 ; 
 scalar_t__ xgene_enet_ring_owner (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_irq_mbox_required(struct xgene_enet_pdata *pdata,
				 struct xgene_enet_desc_ring *ring)
{
	if ((pdata->enet_id == XGENE_ENET2) &&
	    (xgene_enet_ring_owner(ring->id) == RING_OWNER_CPU)) {
		return true;
	}

	return false;
}