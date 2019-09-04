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
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCS_CONTROL_1 ; 
 int PCS_CTRL_PCS_RST ; 
 int /*<<< orphan*/  xgene_enet_rd_pcs (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_enet_wr_pcs (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_pcs_reset(struct xgene_enet_pdata *pdata)
{
	u32 data;

	if (!xgene_enet_rd_pcs(pdata, PCS_CONTROL_1, &data))
		return;

	xgene_enet_wr_pcs(pdata, PCS_CONTROL_1, data | PCS_CTRL_PCS_RST);
	xgene_enet_wr_pcs(pdata, PCS_CONTROL_1, data & ~PCS_CTRL_PCS_RST);
}