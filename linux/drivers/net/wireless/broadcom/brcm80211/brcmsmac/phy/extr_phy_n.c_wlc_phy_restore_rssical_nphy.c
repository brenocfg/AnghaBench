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
struct TYPE_4__ {int /*<<< orphan*/ * rssical_phyregs_5G; int /*<<< orphan*/ * rssical_radio_regs_5G; int /*<<< orphan*/ * rssical_phyregs_2G; int /*<<< orphan*/ * rssical_radio_regs_2G; } ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ nphy_rssical_chanspec_2G; scalar_t__ nphy_rssical_chanspec_5G; TYPE_2__ rssical_cache; TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int RADIO_2056_RX0 ; 
 int RADIO_2056_RX1 ; 
 int RADIO_2056_RX_RSSI_MISC ; 
 int /*<<< orphan*/  RADIO_2056_VCM_MASK ; 
 int RADIO_2057_NB_MASTER_CORE0 ; 
 int RADIO_2057_NB_MASTER_CORE1 ; 
 int /*<<< orphan*/  RADIO_2057_VCM_MASK ; 
 int /*<<< orphan*/  mod_radio_reg (struct brcms_phy*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_phy_reg (struct brcms_phy*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wlc_phy_restore_rssical_nphy(struct brcms_phy *pi)
{
	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if (pi->nphy_rssical_chanspec_2G == 0)
			return;

		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			mod_radio_reg(pi, RADIO_2057_NB_MASTER_CORE0,
				      RADIO_2057_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_2G[0]);
			mod_radio_reg(pi, RADIO_2057_NB_MASTER_CORE1,
				      RADIO_2057_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_2G[1]);
		} else {
			mod_radio_reg(pi,
				      RADIO_2056_RX_RSSI_MISC | RADIO_2056_RX0,
				      RADIO_2056_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_2G[0]);
			mod_radio_reg(pi,
				      RADIO_2056_RX_RSSI_MISC | RADIO_2056_RX1,
				      RADIO_2056_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_2G[1]);
		}

		write_phy_reg(pi, 0x1a6,
			      pi->rssical_cache.rssical_phyregs_2G[0]);
		write_phy_reg(pi, 0x1ac,
			      pi->rssical_cache.rssical_phyregs_2G[1]);
		write_phy_reg(pi, 0x1b2,
			      pi->rssical_cache.rssical_phyregs_2G[2]);
		write_phy_reg(pi, 0x1b8,
			      pi->rssical_cache.rssical_phyregs_2G[3]);
		write_phy_reg(pi, 0x1a4,
			      pi->rssical_cache.rssical_phyregs_2G[4]);
		write_phy_reg(pi, 0x1aa,
			      pi->rssical_cache.rssical_phyregs_2G[5]);
		write_phy_reg(pi, 0x1b0,
			      pi->rssical_cache.rssical_phyregs_2G[6]);
		write_phy_reg(pi, 0x1b6,
			      pi->rssical_cache.rssical_phyregs_2G[7]);
		write_phy_reg(pi, 0x1a5,
			      pi->rssical_cache.rssical_phyregs_2G[8]);
		write_phy_reg(pi, 0x1ab,
			      pi->rssical_cache.rssical_phyregs_2G[9]);
		write_phy_reg(pi, 0x1b1,
			      pi->rssical_cache.rssical_phyregs_2G[10]);
		write_phy_reg(pi, 0x1b7,
			      pi->rssical_cache.rssical_phyregs_2G[11]);

	} else {
		if (pi->nphy_rssical_chanspec_5G == 0)
			return;

		if (NREV_GE(pi->pubpi.phy_rev, 7)) {
			mod_radio_reg(pi, RADIO_2057_NB_MASTER_CORE0,
				      RADIO_2057_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_5G[0]);
			mod_radio_reg(pi, RADIO_2057_NB_MASTER_CORE1,
				      RADIO_2057_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_5G[1]);
		} else {
			mod_radio_reg(pi,
				      RADIO_2056_RX_RSSI_MISC | RADIO_2056_RX0,
				      RADIO_2056_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_5G[0]);
			mod_radio_reg(pi,
				      RADIO_2056_RX_RSSI_MISC | RADIO_2056_RX1,
				      RADIO_2056_VCM_MASK,
				      pi->rssical_cache.
				      rssical_radio_regs_5G[1]);
		}

		write_phy_reg(pi, 0x1a6,
			      pi->rssical_cache.rssical_phyregs_5G[0]);
		write_phy_reg(pi, 0x1ac,
			      pi->rssical_cache.rssical_phyregs_5G[1]);
		write_phy_reg(pi, 0x1b2,
			      pi->rssical_cache.rssical_phyregs_5G[2]);
		write_phy_reg(pi, 0x1b8,
			      pi->rssical_cache.rssical_phyregs_5G[3]);
		write_phy_reg(pi, 0x1a4,
			      pi->rssical_cache.rssical_phyregs_5G[4]);
		write_phy_reg(pi, 0x1aa,
			      pi->rssical_cache.rssical_phyregs_5G[5]);
		write_phy_reg(pi, 0x1b0,
			      pi->rssical_cache.rssical_phyregs_5G[6]);
		write_phy_reg(pi, 0x1b6,
			      pi->rssical_cache.rssical_phyregs_5G[7]);
		write_phy_reg(pi, 0x1a5,
			      pi->rssical_cache.rssical_phyregs_5G[8]);
		write_phy_reg(pi, 0x1ab,
			      pi->rssical_cache.rssical_phyregs_5G[9]);
		write_phy_reg(pi, 0x1b1,
			      pi->rssical_cache.rssical_phyregs_5G[10]);
		write_phy_reg(pi, 0x1b7,
			      pi->rssical_cache.rssical_phyregs_5G[11]);
	}
}