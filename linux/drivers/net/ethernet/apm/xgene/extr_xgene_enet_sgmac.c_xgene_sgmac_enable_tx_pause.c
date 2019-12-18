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
struct xgene_enet_pdata {scalar_t__ enet_id; int port_id; } ;

/* Variables and functions */
 int CSR_ECM_CFG_0_ADDR ; 
 int CSR_ECM_CFG_1_ADDR ; 
 int MULTI_DPF_AUTOCTRL ; 
 int PAUSE_XON_EN ; 
 scalar_t__ XGENE_ENET1 ; 
 int XG_MCX_ECM_CFG_0_ADDR ; 
 int xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,int) ; 
 int /*<<< orphan*/  xgene_enet_wr_mcx_csr (struct xgene_enet_pdata*,int,int) ; 

__attribute__((used)) static void xgene_sgmac_enable_tx_pause(struct xgene_enet_pdata *p, bool enable)
{
	u32 data, ecm_cfg_addr;

	if (p->enet_id == XGENE_ENET1) {
		ecm_cfg_addr = (!(p->port_id % 2)) ? CSR_ECM_CFG_0_ADDR :
				CSR_ECM_CFG_1_ADDR;
	} else {
		ecm_cfg_addr = XG_MCX_ECM_CFG_0_ADDR;
	}

	data = xgene_enet_rd_mcx_csr(p, ecm_cfg_addr);
	if (enable)
		data |= MULTI_DPF_AUTOCTRL | PAUSE_XON_EN;
	else
		data &= ~(MULTI_DPF_AUTOCTRL | PAUSE_XON_EN);
	xgene_enet_wr_mcx_csr(p, ecm_cfg_addr, data);
}