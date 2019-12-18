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
typedef  int u16 ;
struct alx_hw {scalar_t__ lnk_patch; } ;

/* Variables and functions */
 int ALX_ANACTRL_DEF ; 
 int ALX_CLDCTRL3_BP_CABLE1TH_DET_GT ; 
 int ALX_CLDCTRL5_BP_VD_HLFBIAS ; 
 int ALX_GREENCFG2_BP_GREEN ; 
 int ALX_GREENCFG2_GATE_DFSE_EN ; 
 int ALX_IER_LINK_DOWN ; 
 int ALX_IER_LINK_UP ; 
 int ALX_LEGCYPS_DEF ; 
 int /*<<< orphan*/  ALX_LPI_CTRL ; 
 int ALX_LPI_CTRL_EN ; 
 int /*<<< orphan*/  ALX_MIIDBG_ANACTRL ; 
 int /*<<< orphan*/  ALX_MIIDBG_GREENCFG2 ; 
 int /*<<< orphan*/  ALX_MIIDBG_LEGCYPS ; 
 int /*<<< orphan*/  ALX_MIIDBG_SRDSYSMOD ; 
 int /*<<< orphan*/  ALX_MIIDBG_SYSMODCTRL ; 
 int /*<<< orphan*/  ALX_MIIDBG_TST100BTCFG ; 
 int /*<<< orphan*/  ALX_MIIDBG_TST10BTCFG ; 
 int /*<<< orphan*/  ALX_MIIEXT_ANEG ; 
 int /*<<< orphan*/  ALX_MIIEXT_CLDCTRL3 ; 
 int /*<<< orphan*/  ALX_MIIEXT_CLDCTRL5 ; 
 int /*<<< orphan*/  ALX_MIIEXT_LOCAL_EEEADV ; 
 int /*<<< orphan*/  ALX_MIIEXT_NLP78 ; 
 int ALX_MIIEXT_NLP78_120M_DEF ; 
 int /*<<< orphan*/  ALX_MIIEXT_PCS ; 
 int /*<<< orphan*/  ALX_MIIEXT_S3DIG10 ; 
 int ALX_MIIEXT_S3DIG10_DEF ; 
 int /*<<< orphan*/  ALX_MIIEXT_VDRVBIAS ; 
 int /*<<< orphan*/  ALX_MII_IER ; 
 int /*<<< orphan*/  ALX_PHY_CTRL ; 
 int ALX_PHY_CTRL_CLS ; 
 int ALX_PHY_CTRL_DSPRST_OUT ; 
 int ALX_PHY_CTRL_DSPRST_TO ; 
 int ALX_PHY_CTRL_GATE_25M ; 
 int ALX_PHY_CTRL_HIB_EN ; 
 int ALX_PHY_CTRL_HIB_PULSE ; 
 int ALX_PHY_CTRL_IDDQ ; 
 int ALX_PHY_CTRL_POWER_DOWN ; 
 int ALX_PHY_CTRL_RST_ANALOG ; 
 int ALX_SRDSYSMOD_DEF ; 
 int ALX_SYSMODCTRL_IECHOADJ_DEF ; 
 int ALX_TST100BTCFG_DEF ; 
 int ALX_TST10BTCFG_DEF ; 
 int ALX_VDRVBIAS_DEF ; 
 int alx_read_mem32 (struct alx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alx_read_phy_dbg (struct alx_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  alx_read_phy_ext (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alx_write_phy_dbg (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alx_write_phy_ext (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  alx_write_phy_reg (struct alx_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

void alx_reset_phy(struct alx_hw *hw)
{
	int i;
	u32 val;
	u16 phy_val;

	/* (DSP)reset PHY core */
	val = alx_read_mem32(hw, ALX_PHY_CTRL);
	val &= ~(ALX_PHY_CTRL_DSPRST_OUT | ALX_PHY_CTRL_IDDQ |
		 ALX_PHY_CTRL_GATE_25M | ALX_PHY_CTRL_POWER_DOWN |
		 ALX_PHY_CTRL_CLS);
	val |= ALX_PHY_CTRL_RST_ANALOG;

	val |= (ALX_PHY_CTRL_HIB_PULSE | ALX_PHY_CTRL_HIB_EN);
	alx_write_mem32(hw, ALX_PHY_CTRL, val);
	udelay(10);
	alx_write_mem32(hw, ALX_PHY_CTRL, val | ALX_PHY_CTRL_DSPRST_OUT);

	for (i = 0; i < ALX_PHY_CTRL_DSPRST_TO; i++)
		udelay(10);

	/* phy power saving & hib */
	alx_write_phy_dbg(hw, ALX_MIIDBG_LEGCYPS, ALX_LEGCYPS_DEF);
	alx_write_phy_dbg(hw, ALX_MIIDBG_SYSMODCTRL,
			  ALX_SYSMODCTRL_IECHOADJ_DEF);
	alx_write_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_VDRVBIAS,
			  ALX_VDRVBIAS_DEF);

	/* EEE advertisement */
	val = alx_read_mem32(hw, ALX_LPI_CTRL);
	alx_write_mem32(hw, ALX_LPI_CTRL, val & ~ALX_LPI_CTRL_EN);
	alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_LOCAL_EEEADV, 0);

	/* phy power saving */
	alx_write_phy_dbg(hw, ALX_MIIDBG_TST10BTCFG, ALX_TST10BTCFG_DEF);
	alx_write_phy_dbg(hw, ALX_MIIDBG_SRDSYSMOD, ALX_SRDSYSMOD_DEF);
	alx_write_phy_dbg(hw, ALX_MIIDBG_TST100BTCFG, ALX_TST100BTCFG_DEF);
	alx_write_phy_dbg(hw, ALX_MIIDBG_ANACTRL, ALX_ANACTRL_DEF);
	alx_read_phy_dbg(hw, ALX_MIIDBG_GREENCFG2, &phy_val);
	alx_write_phy_dbg(hw, ALX_MIIDBG_GREENCFG2,
			  phy_val & ~ALX_GREENCFG2_GATE_DFSE_EN);
	/* rtl8139c, 120m issue */
	alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_NLP78,
			  ALX_MIIEXT_NLP78_120M_DEF);
	alx_write_phy_ext(hw, ALX_MIIEXT_ANEG, ALX_MIIEXT_S3DIG10,
			  ALX_MIIEXT_S3DIG10_DEF);

	if (hw->lnk_patch) {
		/* Turn off half amplitude */
		alx_read_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL3,
				 &phy_val);
		alx_write_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL3,
				  phy_val | ALX_CLDCTRL3_BP_CABLE1TH_DET_GT);
		/* Turn off Green feature */
		alx_read_phy_dbg(hw, ALX_MIIDBG_GREENCFG2, &phy_val);
		alx_write_phy_dbg(hw, ALX_MIIDBG_GREENCFG2,
				  phy_val | ALX_GREENCFG2_BP_GREEN);
		/* Turn off half Bias */
		alx_read_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL5,
				 &phy_val);
		alx_write_phy_ext(hw, ALX_MIIEXT_PCS, ALX_MIIEXT_CLDCTRL5,
				  phy_val | ALX_CLDCTRL5_BP_VD_HLFBIAS);
	}

	/* set phy interrupt mask */
	alx_write_phy_reg(hw, ALX_MII_IER, ALX_IER_LINK_UP | ALX_IER_LINK_DOWN);
}