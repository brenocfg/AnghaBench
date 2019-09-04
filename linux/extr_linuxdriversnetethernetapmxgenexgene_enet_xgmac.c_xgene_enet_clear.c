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
struct xgene_enet_pdata {int dummy; } ;
struct xgene_enet_desc_ring {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENET_CFGSSQMIFPRESET_ADDR ; 
 int /*<<< orphan*/  ENET_CFGSSQMIWQRESET_ADDR ; 
 int /*<<< orphan*/  xgene_enet_get_fpsel (int /*<<< orphan*/ ) ; 
 scalar_t__ xgene_enet_is_bufpool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_ring_bufnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_ring_if (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_clear(struct xgene_enet_pdata *pdata,
			     struct xgene_enet_desc_ring *ring)
{
	u32 addr, data;

	if (xgene_enet_is_bufpool(ring->id)) {
		addr = ENET_CFGSSQMIFPRESET_ADDR;
		data = BIT(xgene_enet_get_fpsel(ring->id));
	} else {
		addr = ENET_CFGSSQMIWQRESET_ADDR;
		data = BIT(xgene_enet_ring_bufnum(ring->id));
	}

	xgene_enet_wr_ring_if(pdata, addr, data);
}