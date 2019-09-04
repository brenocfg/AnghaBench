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
typedef  scalar_t__ u32 ;
struct xgene_enet_pdata {scalar_t__ enet_id; int port_id; } ;

/* Variables and functions */
 scalar_t__ ECM_CONFIG0_REG_0_ADDR ; 
 scalar_t__ ECM_DROP_COUNT (scalar_t__) ; 
 scalar_t__ ICM_DROP_COUNT (scalar_t__) ; 
 scalar_t__ ICM_ECM_DROP_COUNT_REG0_ADDR ; 
 int OFFSET_4 ; 
 scalar_t__ XGENE_ENET1 ; 
 scalar_t__ XG_MCX_ECM_CONFIG0_REG_0_ADDR ; 
 scalar_t__ XG_MCX_ICM_ECM_DROP_COUNT_REG0_ADDR ; 
 scalar_t__ xgene_enet_rd_mcx_csr (struct xgene_enet_pdata*,scalar_t__) ; 

__attribute__((used)) static void xgene_sgmac_get_drop_cnt(struct xgene_enet_pdata *pdata,
				     u32 *rx, u32 *tx)
{
	u32 addr, count;

	addr = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ICM_ECM_DROP_COUNT_REG0_ADDR :
		ICM_ECM_DROP_COUNT_REG0_ADDR + pdata->port_id * OFFSET_4;
	count = xgene_enet_rd_mcx_csr(pdata, addr);
	*rx = ICM_DROP_COUNT(count);
	*tx = ECM_DROP_COUNT(count);
	/* Errata: 10GE_4 - ICM_ECM_DROP_COUNT not clear-on-read */
	addr = (pdata->enet_id != XGENE_ENET1) ?
		XG_MCX_ECM_CONFIG0_REG_0_ADDR :
		ECM_CONFIG0_REG_0_ADDR + pdata->port_id * OFFSET_4;
	xgene_enet_rd_mcx_csr(pdata, addr);
}