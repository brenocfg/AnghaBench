#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct xgene_enet_pdata {TYPE_1__* mac_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_tx_pause ) (struct xgene_enet_pdata*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AXGMAC_CONFIG_1 ; 
 int /*<<< orphan*/  HSTTCTLEN ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*,int) ; 
 int /*<<< orphan*/  xgene_enet_rd_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_wr_mac (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_xgmac_flowctl_tx(struct xgene_enet_pdata *pdata, bool enable)
{
	u32 data;

	data = xgene_enet_rd_mac(pdata, AXGMAC_CONFIG_1);

	if (enable)
		data |= HSTTCTLEN;
	else
		data &= ~HSTTCTLEN;

	xgene_enet_wr_mac(pdata, AXGMAC_CONFIG_1, data);

	pdata->mac_ops->enable_tx_pause(pdata, enable);
}