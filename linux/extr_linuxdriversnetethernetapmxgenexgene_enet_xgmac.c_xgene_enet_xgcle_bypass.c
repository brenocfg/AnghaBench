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
typedef  int /*<<< orphan*/  u16 ;
struct xgene_enet_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_CLE_BYPASS_EN0 ; 
 int /*<<< orphan*/  CFG_CLE_DSTQID0_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_CLE_FPSEL0_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_CLE_IP_PROTOCOL0_SET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CFG_CLE_NXTFPSEL0_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCLE_BYPASS_REG0_ADDR ; 
 int /*<<< orphan*/  XCLE_BYPASS_REG1_ADDR ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_get_fpsel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_enet_rd_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_enet_wr_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_enet_xgcle_bypass(struct xgene_enet_pdata *pdata,
				    u32 dst_ring_num, u16 bufpool_id,
				    u16 nxtbufpool_id)
{
	u32 cb, fpsel, nxtfpsel;

	xgene_enet_rd_csr(pdata, XCLE_BYPASS_REG0_ADDR, &cb);
	cb |= CFG_CLE_BYPASS_EN0;
	CFG_CLE_IP_PROTOCOL0_SET(&cb, 3);
	xgene_enet_wr_csr(pdata, XCLE_BYPASS_REG0_ADDR, cb);

	fpsel = xgene_enet_get_fpsel(bufpool_id);
	nxtfpsel = xgene_enet_get_fpsel(nxtbufpool_id);
	xgene_enet_rd_csr(pdata, XCLE_BYPASS_REG1_ADDR, &cb);
	CFG_CLE_DSTQID0_SET(&cb, dst_ring_num);
	CFG_CLE_FPSEL0_SET(&cb, fpsel);
	CFG_CLE_NXTFPSEL0_SET(&cb, nxtfpsel);
	xgene_enet_wr_csr(pdata, XCLE_BYPASS_REG1_ADDR, cb);
	pr_info("+ cle_bypass: fpsel: %d nxtfpsel: %d\n", fpsel, nxtfpsel);
}