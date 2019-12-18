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
struct pipe3_settings {int ana_interface; int ana_losd; int dig_hs_rate; int dig_ovrd_hs_rate; int dig_fastlock; int dig_lbw; int dig_stepcnt; int dig_stl; int dig_thr; int dig_thr_mode; int dig_2ndo_sdm_mode; int dll_trim_sel; int dll_phint_rate; int eq_lev; int eq_ftc; int eq_ctl; int eq_ovrd_lev; int eq_ovrd_ftc; } ;
struct ti_pipe3 {scalar_t__ mode; int /*<<< orphan*/  phy_rx; struct pipe3_settings settings; } ;

/* Variables and functions */
 int INTERFACE_MASK ; 
 int INTERFACE_SHIFT ; 
 int LOSD_MASK ; 
 int LOSD_SHIFT ; 
 int MEM_CDR_2NDO_SDM_MODE ; 
 int MEM_CDR_2NDO_SDM_MODE_SHIFT ; 
 int MEM_CDR_FASTLOCK ; 
 int MEM_CDR_FASTLOCK_SHIFT ; 
 int MEM_CDR_LBW_MASK ; 
 int MEM_CDR_LBW_SHIFT ; 
 int MEM_CDR_LOS_SOURCE_MASK ; 
 int MEM_CDR_STEPCNT_MASK ; 
 int MEM_CDR_STEPCNT_SHIFT ; 
 int MEM_CDR_STL_MASK ; 
 int MEM_CDR_STL_SHIFT ; 
 int MEM_CDR_THR_MASK ; 
 int MEM_CDR_THR_MODE ; 
 int MEM_CDR_THR_MODE_SHIFT ; 
 int MEM_CDR_THR_SHIFT ; 
 int MEM_DLL_PHINT_RATE_MASK ; 
 int MEM_DLL_PHINT_RATE_SHIFT ; 
 int MEM_DLL_TRIM_SEL_MASK ; 
 int MEM_DLL_TRIM_SHIFT ; 
 int MEM_EQCTL_MASK ; 
 int MEM_EQCTL_SHIFT ; 
 int MEM_EQFTC_MASK ; 
 int MEM_EQFTC_SHIFT ; 
 int MEM_EQLEV_MASK ; 
 int MEM_EQLEV_SHIFT ; 
 int MEM_HS_RATE_MASK ; 
 int MEM_HS_RATE_SHIFT ; 
 int MEM_OVRD_EQFTC ; 
 int MEM_OVRD_EQFTC_SHIFT ; 
 int MEM_OVRD_EQLEV ; 
 int MEM_OVRD_EQLEV_SHIFT ; 
 int MEM_OVRD_HS_RATE ; 
 int MEM_OVRD_HS_RATE_SHIFT ; 
 int MEM_PLLDIV ; 
 scalar_t__ PIPE3_MODE_SATA ; 
 int /*<<< orphan*/  PIPE3_PHY_RX_ANA_PROGRAMMABILITY ; 
 int /*<<< orphan*/  PIPE3_PHY_RX_DIGITAL_MODES ; 
 int /*<<< orphan*/  PIPE3_PHY_RX_DLL ; 
 int /*<<< orphan*/  PIPE3_PHY_RX_EQUALIZER ; 
 int /*<<< orphan*/  PIPE3_PHY_RX_TRIM ; 
 int /*<<< orphan*/  SATA_PHY_RX_IO_AND_A2D_OVERRIDES ; 
 int ti_pipe3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_pipe3_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ti_pipe3_calibrate(struct ti_pipe3 *phy)
{
	u32 val;
	struct pipe3_settings *s = &phy->settings;

	val = ti_pipe3_readl(phy->phy_rx, PIPE3_PHY_RX_ANA_PROGRAMMABILITY);
	val &= ~(INTERFACE_MASK | LOSD_MASK | MEM_PLLDIV);
	val |= (s->ana_interface << INTERFACE_SHIFT | s->ana_losd << LOSD_SHIFT);
	ti_pipe3_writel(phy->phy_rx, PIPE3_PHY_RX_ANA_PROGRAMMABILITY, val);

	val = ti_pipe3_readl(phy->phy_rx, PIPE3_PHY_RX_DIGITAL_MODES);
	val &= ~(MEM_HS_RATE_MASK | MEM_OVRD_HS_RATE | MEM_CDR_FASTLOCK |
		 MEM_CDR_LBW_MASK | MEM_CDR_STEPCNT_MASK | MEM_CDR_STL_MASK |
		 MEM_CDR_THR_MASK | MEM_CDR_THR_MODE | MEM_CDR_2NDO_SDM_MODE);
	val |= s->dig_hs_rate << MEM_HS_RATE_SHIFT |
		s->dig_ovrd_hs_rate << MEM_OVRD_HS_RATE_SHIFT |
		s->dig_fastlock << MEM_CDR_FASTLOCK_SHIFT |
		s->dig_lbw << MEM_CDR_LBW_SHIFT |
		s->dig_stepcnt << MEM_CDR_STEPCNT_SHIFT |
		s->dig_stl << MEM_CDR_STL_SHIFT |
		s->dig_thr << MEM_CDR_THR_SHIFT |
		s->dig_thr_mode << MEM_CDR_THR_MODE_SHIFT |
		s->dig_2ndo_sdm_mode << MEM_CDR_2NDO_SDM_MODE_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PIPE3_PHY_RX_DIGITAL_MODES, val);

	val = ti_pipe3_readl(phy->phy_rx, PIPE3_PHY_RX_TRIM);
	val &= ~MEM_DLL_TRIM_SEL_MASK;
	val |= s->dll_trim_sel << MEM_DLL_TRIM_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PIPE3_PHY_RX_TRIM, val);

	val = ti_pipe3_readl(phy->phy_rx, PIPE3_PHY_RX_DLL);
	val &= ~MEM_DLL_PHINT_RATE_MASK;
	val |= s->dll_phint_rate << MEM_DLL_PHINT_RATE_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PIPE3_PHY_RX_DLL, val);

	val = ti_pipe3_readl(phy->phy_rx, PIPE3_PHY_RX_EQUALIZER);
	val &= ~(MEM_EQLEV_MASK | MEM_EQFTC_MASK | MEM_EQCTL_MASK |
		 MEM_OVRD_EQLEV | MEM_OVRD_EQFTC);
	val |= s->eq_lev << MEM_EQLEV_SHIFT |
		s->eq_ftc << MEM_EQFTC_SHIFT |
		s->eq_ctl << MEM_EQCTL_SHIFT |
		s->eq_ovrd_lev << MEM_OVRD_EQLEV_SHIFT |
		s->eq_ovrd_ftc << MEM_OVRD_EQFTC_SHIFT;
	ti_pipe3_writel(phy->phy_rx, PIPE3_PHY_RX_EQUALIZER, val);

	if (phy->mode == PIPE3_MODE_SATA) {
		val = ti_pipe3_readl(phy->phy_rx,
				     SATA_PHY_RX_IO_AND_A2D_OVERRIDES);
		val &= ~MEM_CDR_LOS_SOURCE_MASK;
		ti_pipe3_writel(phy->phy_rx, SATA_PHY_RX_IO_AND_A2D_OVERRIDES,
				val);
	}
}