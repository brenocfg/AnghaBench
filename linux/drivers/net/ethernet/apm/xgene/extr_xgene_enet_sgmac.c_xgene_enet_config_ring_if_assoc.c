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
struct xgene_enet_pdata {scalar_t__ enet_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_CFGSSQMIFPQASSOC_ADDR ; 
 int /*<<< orphan*/  ENET_CFGSSQMIWQASSOC_ADDR ; 
 scalar_t__ XGENE_ENET1 ; 
 int /*<<< orphan*/  xgene_enet_wr_ring_if (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_enet_config_ring_if_assoc(struct xgene_enet_pdata *p)
{
	u32 val;

	val = (p->enet_id == XGENE_ENET1) ? 0xffffffff : 0;
	xgene_enet_wr_ring_if(p, ENET_CFGSSQMIWQASSOC_ADDR, val);
	xgene_enet_wr_ring_if(p, ENET_CFGSSQMIFPQASSOC_ADDR, val);
}