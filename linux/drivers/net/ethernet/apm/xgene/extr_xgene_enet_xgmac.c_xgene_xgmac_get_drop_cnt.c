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

/* Variables and functions */
 int /*<<< orphan*/  ECM_DROP_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICM_DROP_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENET_ECM_CONFIG0_REG_0 ; 
 int /*<<< orphan*/  XGENET_ICM_ECM_DROP_COUNT_REG0 ; 
 int /*<<< orphan*/  xgene_enet_rd_axg_csr (struct xgene_enet_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xgene_xgmac_get_drop_cnt(struct xgene_enet_pdata *pdata,
				     u32 *rx, u32 *tx)
{
	u32 count;

	xgene_enet_rd_axg_csr(pdata, XGENET_ICM_ECM_DROP_COUNT_REG0, &count);
	*rx = ICM_DROP_COUNT(count);
	*tx = ECM_DROP_COUNT(count);
	/* Errata: 10GE_4 - ICM_ECM_DROP_COUNT not clear-on-read */
	xgene_enet_rd_axg_csr(pdata, XGENET_ECM_CONFIG0_REG_0, &count);
}