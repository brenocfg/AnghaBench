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
typedef  int u16 ;
struct skge_port {int port; scalar_t__ flow_status; scalar_t__ duplex; struct skge_hw* hw; } ;
struct skge_hw {scalar_t__ phy_type; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ FLOW_STAT_LOC_SEND ; 
 scalar_t__ FLOW_STAT_NONE ; 
 scalar_t__ FLOW_STAT_SYMMETRIC ; 
 int /*<<< orphan*/  MFF_DIS_PAUSE ; 
 int /*<<< orphan*/  MFF_ENA_PAUSE ; 
 int /*<<< orphan*/  PHY_BCOM_AUX_CTRL ; 
 int /*<<< orphan*/  PHY_BCOM_INT_MASK ; 
 int PHY_B_AC_DIS_PM ; 
 int PHY_B_DEF_MSK ; 
 int /*<<< orphan*/  RX_MFF_CTRL1 ; 
 scalar_t__ SK_PHY_BCOM ; 
 scalar_t__ SK_PHY_XMAC ; 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XM_IMSK ; 
 int /*<<< orphan*/  XM_ISRC ; 
 int XM_IS_TXF_UR ; 
 int /*<<< orphan*/  XM_MAC_PTIME ; 
 int /*<<< orphan*/  XM_MMU_CMD ; 
 int XM_MMU_ENA_RX ; 
 int XM_MMU_ENA_TX ; 
 int XM_MMU_GMII_FD ; 
 int XM_MMU_IGN_PF ; 
 int /*<<< orphan*/  XM_MODE ; 
 int /*<<< orphan*/  XM_PAUSE_MODE ; 
 int /*<<< orphan*/  skge_link_up (struct skge_port*) ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int xm_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_read32 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xm_write32 (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genesis_link_up(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u16 cmd, msk;
	u32 mode;

	cmd = xm_read16(hw, port, XM_MMU_CMD);

	/*
	 * enabling pause frame reception is required for 1000BT
	 * because the XMAC is not reset if the link is going down
	 */
	if (skge->flow_status == FLOW_STAT_NONE ||
	    skge->flow_status == FLOW_STAT_LOC_SEND)
		/* Disable Pause Frame Reception */
		cmd |= XM_MMU_IGN_PF;
	else
		/* Enable Pause Frame Reception */
		cmd &= ~XM_MMU_IGN_PF;

	xm_write16(hw, port, XM_MMU_CMD, cmd);

	mode = xm_read32(hw, port, XM_MODE);
	if (skge->flow_status == FLOW_STAT_SYMMETRIC ||
	    skge->flow_status == FLOW_STAT_LOC_SEND) {
		/*
		 * Configure Pause Frame Generation
		 * Use internal and external Pause Frame Generation.
		 * Sending pause frames is edge triggered.
		 * Send a Pause frame with the maximum pause time if
		 * internal oder external FIFO full condition occurs.
		 * Send a zero pause time frame to re-start transmission.
		 */
		/* XM_PAUSE_DA = '010000C28001' (default) */
		/* XM_MAC_PTIME = 0xffff (maximum) */
		/* remember this value is defined in big endian (!) */
		xm_write16(hw, port, XM_MAC_PTIME, 0xffff);

		mode |= XM_PAUSE_MODE;
		skge_write16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_PAUSE);
	} else {
		/*
		 * disable pause frame generation is required for 1000BT
		 * because the XMAC is not reset if the link is going down
		 */
		/* Disable Pause Mode in Mode Register */
		mode &= ~XM_PAUSE_MODE;

		skge_write16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_DIS_PAUSE);
	}

	xm_write32(hw, port, XM_MODE, mode);

	/* Turn on detection of Tx underrun */
	msk = xm_read16(hw, port, XM_IMSK);
	msk &= ~XM_IS_TXF_UR;
	xm_write16(hw, port, XM_IMSK, msk);

	xm_read16(hw, port, XM_ISRC);

	/* get MMU Command Reg. */
	cmd = xm_read16(hw, port, XM_MMU_CMD);
	if (hw->phy_type != SK_PHY_XMAC && skge->duplex == DUPLEX_FULL)
		cmd |= XM_MMU_GMII_FD;

	/*
	 * Workaround BCOM Errata (#10523) for all BCom Phys
	 * Enable Power Management after link up
	 */
	if (hw->phy_type == SK_PHY_BCOM) {
		xm_phy_write(hw, port, PHY_BCOM_AUX_CTRL,
			     xm_phy_read(hw, port, PHY_BCOM_AUX_CTRL)
			     & ~PHY_B_AC_DIS_PM);
		xm_phy_write(hw, port, PHY_BCOM_INT_MASK, PHY_B_DEF_MSK);
	}

	/* enable Rx/Tx */
	xm_write16(hw, port, XM_MMU_CMD,
			cmd | XM_MMU_ENA_RX | XM_MMU_ENA_TX);
	skge_link_up(skge);
}