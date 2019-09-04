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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENET_CFGSSQMIFPQASSOC_ADDR ; 
 int /*<<< orphan*/  ENET_CFGSSQMIQMLITEFPQASSOC_ADDR ; 
 int /*<<< orphan*/  ENET_CFGSSQMIQMLITEWQASSOC_ADDR ; 
 int /*<<< orphan*/  ENET_CFGSSQMIWQASSOC_ADDR ; 
 int /*<<< orphan*/  xgene_enet_wr_ring_if (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_config_ring_if_assoc(struct xgene_enet_pdata *pdata)
{
	xgene_enet_wr_ring_if(pdata, ENET_CFGSSQMIWQASSOC_ADDR, 0);
	xgene_enet_wr_ring_if(pdata, ENET_CFGSSQMIFPQASSOC_ADDR, 0);
	xgene_enet_wr_ring_if(pdata, ENET_CFGSSQMIQMLITEWQASSOC_ADDR, 0);
	xgene_enet_wr_ring_if(pdata, ENET_CFGSSQMIQMLITEFPQASSOC_ADDR, 0);
}