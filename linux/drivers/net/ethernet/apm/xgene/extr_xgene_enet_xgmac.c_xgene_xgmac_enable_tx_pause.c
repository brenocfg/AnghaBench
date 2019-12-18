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
 int MULTI_DPF_AUTOCTRL ; 
 int PAUSE_XON_EN ; 
 int /*<<< orphan*/  XGENET_CSR_ECM_CFG_0_ADDR ; 
 int /*<<< orphan*/  xgene_enet_rd_axg_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  xgene_enet_wr_axg_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_xgmac_enable_tx_pause(struct xgene_enet_pdata *pdata,
					bool enable)
{
	u32 data;

	xgene_enet_rd_axg_csr(pdata, XGENET_CSR_ECM_CFG_0_ADDR, &data);

	if (enable)
		data |= MULTI_DPF_AUTOCTRL | PAUSE_XON_EN;
	else
		data &= ~(MULTI_DPF_AUTOCTRL | PAUSE_XON_EN);

	xgene_enet_wr_axg_csr(pdata, XGENET_CSR_ECM_CFG_0_ADDR, data);
}