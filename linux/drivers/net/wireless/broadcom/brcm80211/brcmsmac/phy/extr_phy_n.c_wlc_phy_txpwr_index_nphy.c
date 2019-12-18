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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {int phy_corenum; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {int nphy_txpwrctrl; scalar_t__ phyhang_avoid; TYPE_3__* nphy_txpwrindex; TYPE_1__* sh; TYPE_2__ pubpi; } ;
typedef  int s8 ;
typedef  int s32 ;
typedef  int s16 ;
struct TYPE_6__ {int index; int AfectrlOverride; int AfeCtrlDacGain; int rad_gain; int bbmult; int iqcomp_a; int locomp; int /*<<< orphan*/  index_internal; int /*<<< orphan*/  index_internal_save; } ;
struct TYPE_4__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int NPHY_TBL_ID_CORE1TXPWRCTL ; 
 int NPHY_TBL_ID_CORE2TXPWRCTL ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFF ; 
 int /*<<< orphan*/  ON ; 
 int PHY_CORE_0 ; 
 scalar_t__ PHY_IPA (struct brcms_phy*) ; 
 int PHY_TPC_HW_OFF ; 
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 void* read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlapi_bmac_phyclk_fgc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlc_phy_table_read_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_table_write_nphy (struct brcms_phy*,int,int,int,int,int*) ; 
 int /*<<< orphan*/  wlc_phy_txpwrctrl_enable_nphy (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int) ; 

void
wlc_phy_txpwr_index_nphy(struct brcms_phy *pi, u8 core_mask, s8 txpwrindex,
			 bool restore_cals)
{
	u8 core, txpwrctl_tbl;
	u16 tx_ind0, iq_ind0, lo_ind0;
	u16 m1m2;
	u32 txgain;
	u16 rad_gain, dac_gain;
	u8 bbmult;
	u32 iqcomp;
	u16 iqcomp_a, iqcomp_b;
	u32 locomp;
	u16 tmpval;
	u8 tx_pwr_ctrl_state;
	s32 rfpwr_offset;
	u16 regval[2];

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, true);

	tx_ind0 = 192;
	iq_ind0 = 320;
	lo_ind0 = 448;

	for (core = 0; core < pi->pubpi.phy_corenum; core++) {

		if ((core_mask & (1 << core)) == 0)
			continue;

		txpwrctl_tbl = (core == PHY_CORE_0) ? 26 : 27;

		if (txpwrindex < 0) {
			if (pi->nphy_txpwrindex[core].index < 0)
				continue;

			if (NREV_GE(pi->pubpi.phy_rev, 3)) {
				mod_phy_reg(pi, 0x8f,
					    (0x1 << 8),
					    pi->nphy_txpwrindex[core].
					    AfectrlOverride);
				mod_phy_reg(pi, 0xa5, (0x1 << 8),
					    pi->nphy_txpwrindex[core].
					    AfectrlOverride);
			} else {
				mod_phy_reg(pi, 0xa5,
					    (0x1 << 14),
					    pi->nphy_txpwrindex[core].
					    AfectrlOverride);
			}

			write_phy_reg(pi, (core == PHY_CORE_0) ?
				      0xaa : 0xab,
				      pi->nphy_txpwrindex[core].AfeCtrlDacGain);

			wlc_phy_table_write_nphy(pi, 7, 1, (0x110 + core), 16,
						 &pi->nphy_txpwrindex[core].
						 rad_gain);

			wlc_phy_table_read_nphy(pi, 15, 1, 87, 16, &m1m2);
			m1m2 &= ((core == PHY_CORE_0) ? 0x00ff : 0xff00);
			m1m2 |= ((core == PHY_CORE_0) ?
				 (pi->nphy_txpwrindex[core].bbmult << 8) :
				 (pi->nphy_txpwrindex[core].bbmult << 0));
			wlc_phy_table_write_nphy(pi, 15, 1, 87, 16, &m1m2);

			if (restore_cals) {
				wlc_phy_table_write_nphy(
					pi, 15, 2, (80 + 2 * core), 16,
					&pi->nphy_txpwrindex[core].iqcomp_a);
				wlc_phy_table_write_nphy(
					pi, 15, 1, (85 + core), 16,
					&pi->nphy_txpwrindex[core].locomp);
				wlc_phy_table_write_nphy(
					pi, 15, 1, (93 + core), 16,
					&pi->nphy_txpwrindex[core].locomp);
			}

			wlc_phy_txpwrctrl_enable_nphy(pi, pi->nphy_txpwrctrl);

			pi->nphy_txpwrindex[core].index_internal =
				pi->nphy_txpwrindex[core].index_internal_save;
		} else {

			if (pi->nphy_txpwrindex[core].index < 0) {

				if (NREV_GE(pi->pubpi.phy_rev, 3)) {
					mod_phy_reg(pi, 0x8f,
						    (0x1 << 8),
						    pi->nphy_txpwrindex[core].
						    AfectrlOverride);
					mod_phy_reg(pi, 0xa5, (0x1 << 8),
						    pi->nphy_txpwrindex[core].
						    AfectrlOverride);
				} else {
					pi->nphy_txpwrindex[core].
					AfectrlOverride =
						read_phy_reg(pi, 0xa5);
				}

				pi->nphy_txpwrindex[core].AfeCtrlDacGain =
					read_phy_reg(pi, (core == PHY_CORE_0) ?
							 0xaa : 0xab);

				wlc_phy_table_read_nphy(pi, 7, 1,
							(0x110 + core), 16,
							&pi->
							nphy_txpwrindex[core].
							rad_gain);

				wlc_phy_table_read_nphy(pi, 15, 1, 87, 16,
							&tmpval);
				tmpval >>= ((core == PHY_CORE_0) ? 8 : 0);
				tmpval &= 0xff;
				pi->nphy_txpwrindex[core].bbmult = (u8) tmpval;

				wlc_phy_table_read_nphy(pi, 15, 2,
							(80 + 2 * core), 16,
							&pi->
							nphy_txpwrindex[core].
							iqcomp_a);

				wlc_phy_table_read_nphy(pi, 15, 1, (85 + core),
							16,
							&pi->
							nphy_txpwrindex[core].
							locomp);

				pi->nphy_txpwrindex[core].index_internal_save =
					pi->nphy_txpwrindex[core].
					index_internal;
			}

			tx_pwr_ctrl_state = pi->nphy_txpwrctrl;
			wlc_phy_txpwrctrl_enable_nphy(pi, PHY_TPC_HW_OFF);

			if (NREV_IS(pi->pubpi.phy_rev, 1))
				wlapi_bmac_phyclk_fgc(pi->sh->physhim, ON);

			wlc_phy_table_read_nphy(pi, txpwrctl_tbl, 1,
						(tx_ind0 + txpwrindex), 32,
						&txgain);

			if (NREV_GE(pi->pubpi.phy_rev, 3))
				rad_gain = (txgain >> 16) &
					   ((1 << (32 - 16 + 1)) - 1);
			else
				rad_gain = (txgain >> 16) &
					   ((1 << (28 - 16 + 1)) - 1);

			dac_gain = (txgain >> 8) & ((1 << (13 - 8 + 1)) - 1);
			bbmult = (txgain >> 0) & ((1 << (7 - 0 + 1)) - 1);

			if (NREV_GE(pi->pubpi.phy_rev, 3))
				mod_phy_reg(pi, ((core == PHY_CORE_0) ? 0x8f :
						 0xa5), (0x1 << 8), (0x1 << 8));
			else
				mod_phy_reg(pi, 0xa5, (0x1 << 14), (0x1 << 14));

			write_phy_reg(pi, (core == PHY_CORE_0) ?
				      0xaa : 0xab, dac_gain);

			wlc_phy_table_write_nphy(pi, 7, 1, (0x110 + core), 16,
						 &rad_gain);

			wlc_phy_table_read_nphy(pi, 15, 1, 87, 16, &m1m2);
			m1m2 &= ((core == PHY_CORE_0) ? 0x00ff : 0xff00);
			m1m2 |= ((core == PHY_CORE_0) ?
				(bbmult << 8) : (bbmult << 0));

			wlc_phy_table_write_nphy(pi, 15, 1, 87, 16, &m1m2);

			wlc_phy_table_read_nphy(pi, txpwrctl_tbl, 1,
						(iq_ind0 + txpwrindex), 32,
						&iqcomp);
			iqcomp_a = (iqcomp >> 10) & ((1 << (19 - 10 + 1)) - 1);
			iqcomp_b = (iqcomp >> 0) & ((1 << (9 - 0 + 1)) - 1);

			if (restore_cals) {
				regval[0] = (u16) iqcomp_a;
				regval[1] = (u16) iqcomp_b;
				wlc_phy_table_write_nphy(pi, 15, 2,
							 (80 + 2 * core), 16,
							 regval);
			}

			wlc_phy_table_read_nphy(pi, txpwrctl_tbl, 1,
						(lo_ind0 + txpwrindex), 32,
						&locomp);
			if (restore_cals)
				wlc_phy_table_write_nphy(pi, 15, 1, (85 + core),
							 16, &locomp);

			if (NREV_IS(pi->pubpi.phy_rev, 1))
				wlapi_bmac_phyclk_fgc(pi->sh->physhim, OFF);

			if (PHY_IPA(pi)) {
				wlc_phy_table_read_nphy(pi,
						(core == PHY_CORE_0 ?
						 NPHY_TBL_ID_CORE1TXPWRCTL :
						 NPHY_TBL_ID_CORE2TXPWRCTL),
						1, 576 + txpwrindex, 32,
						&rfpwr_offset);

				mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
					    0x29b, (0x1ff << 4),
					    ((s16) rfpwr_offset) << 4);

				mod_phy_reg(pi, (core == PHY_CORE_0) ? 0x297 :
					    0x29b, (0x1 << 2), (1) << 2);

			}

			wlc_phy_txpwrctrl_enable_nphy(pi, tx_pwr_ctrl_state);
		}

		pi->nphy_txpwrindex[core].index = txpwrindex;
	}

	if (pi->phyhang_avoid)
		wlc_phy_stay_in_carriersearch_nphy(pi, false);
}