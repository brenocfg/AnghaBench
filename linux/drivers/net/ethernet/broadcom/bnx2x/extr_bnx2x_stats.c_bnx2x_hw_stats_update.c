#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nig_stats {scalar_t__ brb_truncate; scalar_t__ brb_discard; } ;
struct mac_stx {int dummy; } ;
struct host_port_stats {int /*<<< orphan*/  host_port_stats_counter; int /*<<< orphan*/  brb_drop_lo; int /*<<< orphan*/  brb_drop_hi; struct nig_stats* mac_stx; } ;
struct bnx2x_eth_stats {scalar_t__ nig_timer_max; int /*<<< orphan*/  eee_tx_lpi; int /*<<< orphan*/  brb_drop_lo; int /*<<< orphan*/  brb_drop_hi; struct nig_stats rx_stat_ifhcinbadoctets_hi; int /*<<< orphan*/  brb_truncate_lo; int /*<<< orphan*/  brb_truncate_hi; } ;
struct TYPE_5__ {int mac_type; } ;
struct TYPE_4__ {struct nig_stats old_nig_stats; } ;
struct bnx2x {TYPE_2__ link_vars; struct bnx2x_eth_stats eth_stats; TYPE_1__ port; } ;
struct TYPE_6__ {int /*<<< orphan*/  stat_nig_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_EXTEND_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_ERR (char*,...) ; 
 int /*<<< orphan*/  BNX2X_MSG_STATS ; 
 int /*<<< orphan*/  BP_NOMCP (struct bnx2x*) ; 
 size_t BP_PORT (struct bnx2x*) ; 
 scalar_t__ CHIP_IS_E3 (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
#define  MAC_TYPE_BMAC 132 
#define  MAC_TYPE_EMAC 131 
#define  MAC_TYPE_NONE 130 
#define  MAC_TYPE_UMAC 129 
#define  MAC_TYPE_XMAC 128 
 scalar_t__ MISC_REG_CPMU_LP_SM_ENT_CNT_P0 ; 
 scalar_t__ MISC_REG_CPMU_LP_SM_ENT_CNT_P1 ; 
 scalar_t__ REG_RD (struct bnx2x*,scalar_t__) ; 
 scalar_t__ SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UPDATE_STAT64_NIG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_bmac_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_emac_stats_update (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_mstat_stats_update (struct bnx2x*) ; 
 void* bnx2x_sp (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  egress_mac_pkt0 ; 
 int /*<<< orphan*/  egress_mac_pkt1 ; 
 int /*<<< orphan*/  etherstatspkts1024octetsto1522octets ; 
 int /*<<< orphan*/  etherstatspktsover1522octets ; 
 int /*<<< orphan*/  memcpy (struct nig_stats*,struct nig_stats*,int) ; 
 int /*<<< orphan*/  nig_stats ; 
 TYPE_3__* port_mb ; 
 int /*<<< orphan*/  port_stats ; 

__attribute__((used)) static int bnx2x_hw_stats_update(struct bnx2x *bp)
{
	struct nig_stats *new = bnx2x_sp(bp, nig_stats);
	struct nig_stats *old = &(bp->port.old_nig_stats);
	struct host_port_stats *pstats = bnx2x_sp(bp, port_stats);
	struct bnx2x_eth_stats *estats = &bp->eth_stats;
	struct {
		u32 lo;
		u32 hi;
	} diff;

	switch (bp->link_vars.mac_type) {
	case MAC_TYPE_BMAC:
		bnx2x_bmac_stats_update(bp);
		break;

	case MAC_TYPE_EMAC:
		bnx2x_emac_stats_update(bp);
		break;

	case MAC_TYPE_UMAC:
	case MAC_TYPE_XMAC:
		bnx2x_mstat_stats_update(bp);
		break;

	case MAC_TYPE_NONE: /* unreached */
		DP(BNX2X_MSG_STATS,
		   "stats updated by DMAE but no MAC active\n");
		return -1;

	default: /* unreached */
		BNX2X_ERR("Unknown MAC type\n");
	}

	ADD_EXTEND_64(pstats->brb_drop_hi, pstats->brb_drop_lo,
		      new->brb_discard - old->brb_discard);
	ADD_EXTEND_64(estats->brb_truncate_hi, estats->brb_truncate_lo,
		      new->brb_truncate - old->brb_truncate);

	if (!CHIP_IS_E3(bp)) {
		UPDATE_STAT64_NIG(egress_mac_pkt0,
					etherstatspkts1024octetsto1522octets);
		UPDATE_STAT64_NIG(egress_mac_pkt1,
					etherstatspktsover1522octets);
	}

	memcpy(old, new, sizeof(struct nig_stats));

	memcpy(&(estats->rx_stat_ifhcinbadoctets_hi), &(pstats->mac_stx[1]),
	       sizeof(struct mac_stx));
	estats->brb_drop_hi = pstats->brb_drop_hi;
	estats->brb_drop_lo = pstats->brb_drop_lo;

	pstats->host_port_stats_counter++;

	if (CHIP_IS_E3(bp)) {
		u32 lpi_reg = BP_PORT(bp) ? MISC_REG_CPMU_LP_SM_ENT_CNT_P1
					  : MISC_REG_CPMU_LP_SM_ENT_CNT_P0;
		estats->eee_tx_lpi += REG_RD(bp, lpi_reg);
	}

	if (!BP_NOMCP(bp)) {
		u32 nig_timer_max =
			SHMEM_RD(bp, port_mb[BP_PORT(bp)].stat_nig_timer);
		if (nig_timer_max != estats->nig_timer_max) {
			estats->nig_timer_max = nig_timer_max;
			BNX2X_ERR("NIG timer max (%u)\n",
				  estats->nig_timer_max);
		}
	}

	return 0;
}