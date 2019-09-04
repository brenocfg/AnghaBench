#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xgene_enet_pdata {int* extd_stats; scalar_t__ phy_mode; int false_rflr; int vlan_rjbr; TYPE_1__* mac_ops; } ;
struct TYPE_4__ {scalar_t__ mask; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_drop_cnt ) (struct xgene_enet_pdata*,int*,int*) ;} ;

/* Variables and functions */
 size_t FALSE_RFLR_IDX ; 
 size_t FALSE_RJBR_IDX ; 
 int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 size_t RALN_IDX ; 
 size_t RFCS_IDX ; 
 size_t RFLR_IDX ; 
 size_t RUND_IDX ; 
 size_t RX_OVERRUN_IDX ; 
 size_t TFCS_IDX ; 
 size_t TFRG_IDX ; 
 size_t TX_UNDERRUN_IDX ; 
 int XGENE_EXTD_STATS_LEN ; 
 TYPE_2__* gstrings_extd_stats ; 
 int /*<<< orphan*/  stub1 (struct xgene_enet_pdata*,int*,int*) ; 
 int xgene_enet_rd_stat (struct xgene_enet_pdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgene_get_extd_stats(struct xgene_enet_pdata *pdata)
{
	u32 rx_drop, tx_drop;
	u32 mask, tmp;
	int i;

	for (i = 0; i < XGENE_EXTD_STATS_LEN; i++) {
		tmp = xgene_enet_rd_stat(pdata, gstrings_extd_stats[i].addr);
		if (gstrings_extd_stats[i].mask) {
			mask = GENMASK(gstrings_extd_stats[i].mask - 1, 0);
			pdata->extd_stats[i] += (tmp & mask);
		}
	}

	if (pdata->phy_mode == PHY_INTERFACE_MODE_XGMII) {
		/* Errata 10GE_10 - SW should intepret RALN as 0 */
		pdata->extd_stats[RALN_IDX] = 0;
	} else {
		/* Errata ENET_15 - Fixes RFCS, RFLR, TFCS counter */
		pdata->extd_stats[RFCS_IDX] -= pdata->extd_stats[RALN_IDX];
		pdata->extd_stats[RFLR_IDX] -= pdata->extd_stats[RUND_IDX];
		pdata->extd_stats[TFCS_IDX] -= pdata->extd_stats[TFRG_IDX];
	}

	pdata->mac_ops->get_drop_cnt(pdata, &rx_drop, &tx_drop);
	pdata->extd_stats[RX_OVERRUN_IDX] += rx_drop;
	pdata->extd_stats[TX_UNDERRUN_IDX] += tx_drop;

	/* Errata 10GE_8 -  Update Frame recovered from Errata 10GE_8/ENET_11 */
	pdata->extd_stats[FALSE_RFLR_IDX] = pdata->false_rflr;
	/* Errata ENET_15 - Jabber Frame recov'ed from Errata 10GE_10/ENET_15 */
	pdata->extd_stats[FALSE_RJBR_IDX] = pdata->vlan_rjbr;
}