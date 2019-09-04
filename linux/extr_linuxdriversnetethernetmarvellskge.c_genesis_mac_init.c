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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct skge_port {scalar_t__ duplex; } ;
struct skge_hw {int phy_type; int ports; struct net_device** dev; } ;
struct net_device {scalar_t__ mtu; int /*<<< orphan*/  const* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  B2_GP_IO ; 
 int /*<<< orphan*/  B3_MA_RCINI_RX1 ; 
 int /*<<< orphan*/  B3_MA_RCINI_RX2 ; 
 int /*<<< orphan*/  B3_MA_RCINI_TX1 ; 
 int /*<<< orphan*/  B3_MA_RCINI_TX2 ; 
 int /*<<< orphan*/  B3_MA_TOINI_RX1 ; 
 int /*<<< orphan*/  B3_MA_TOINI_RX2 ; 
 int /*<<< orphan*/  B3_MA_TOINI_TX1 ; 
 int /*<<< orphan*/  B3_MA_TOINI_TX2 ; 
 int /*<<< orphan*/  B3_MA_TO_CTRL ; 
 int /*<<< orphan*/  B3_PA_CTRL ; 
 scalar_t__ DUPLEX_HALF ; 
 scalar_t__ ETH_DATA_LEN ; 
 int GP_DIR_0 ; 
 int GP_DIR_2 ; 
 int GP_IO_0 ; 
 int GP_IO_2 ; 
 int MA_RST_CLR ; 
 int MFF_CLR_MAC_RST ; 
 int MFF_ENA_FLUSH ; 
 int MFF_ENA_OP_MD ; 
 int MFF_ENA_TIM_PAT ; 
 int MFF_RST_CLR ; 
 int MFF_SET_MAC_RST ; 
 int MFF_TX_CTRL_DEF ; 
 int PA_ENA_TO_TX1 ; 
 int PA_ENA_TO_TX2 ; 
 int /*<<< orphan*/  RX_MFF_CTRL1 ; 
 int /*<<< orphan*/  RX_MFF_CTRL2 ; 
#define  SK_PHY_BCOM 129 
#define  SK_PHY_XMAC 128 
 int /*<<< orphan*/  SK_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_MFF_CTRL1 ; 
 int /*<<< orphan*/  TX_MFF_CTRL2 ; 
 int /*<<< orphan*/  XMR_DEF_MSK ; 
 int /*<<< orphan*/  XMT_DEF_MSK ; 
 int /*<<< orphan*/  XM_DEF_MODE ; 
 int /*<<< orphan*/  XM_EXM (int) ; 
 int /*<<< orphan*/  XM_HW_CFG ; 
 int XM_HW_GMII_MD ; 
 int /*<<< orphan*/  XM_MODE ; 
 int XM_RX_BIG_PK_OK ; 
 int /*<<< orphan*/  XM_RX_CMD ; 
 int XM_RX_DIS_CEXT ; 
 int /*<<< orphan*/  XM_RX_EV_MSK ; 
 int /*<<< orphan*/  XM_RX_HI_WM ; 
 int XM_RX_LENERR_OK ; 
 int XM_RX_STRIP_FCS ; 
 int /*<<< orphan*/  XM_SA ; 
 int XM_SC_CLR_RXC ; 
 int XM_SC_CLR_TXC ; 
 int /*<<< orphan*/  XM_STAT_CMD ; 
 int XM_TX_AUTO_PAD ; 
 int /*<<< orphan*/  XM_TX_CMD ; 
 int /*<<< orphan*/  XM_TX_EV_MSK ; 
 int /*<<< orphan*/  XM_TX_THR ; 
 int /*<<< orphan*/  bcom_check_link (struct skge_hw*,int) ; 
 int /*<<< orphan*/  bcom_phy_init (struct skge_port*) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int skge_read16 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int skge_read32 (struct skge_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_write16 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write32 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skge_write8 (struct skge_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  xm_outaddr (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  xm_phy_init (struct skge_port*) ; 
 int /*<<< orphan*/  xm_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xm_write32 (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void genesis_mac_init(struct skge_hw *hw, int port)
{
	struct net_device *dev = hw->dev[port];
	struct skge_port *skge = netdev_priv(dev);
	int jumbo = hw->dev[port]->mtu > ETH_DATA_LEN;
	int i;
	u32 r;
	static const u8 zero[6]  = { 0 };

	for (i = 0; i < 10; i++) {
		skge_write16(hw, SK_REG(port, TX_MFF_CTRL1),
			     MFF_SET_MAC_RST);
		if (skge_read16(hw, SK_REG(port, TX_MFF_CTRL1)) & MFF_SET_MAC_RST)
			goto reset_ok;
		udelay(1);
	}

	netdev_warn(dev, "genesis reset failed\n");

 reset_ok:
	/* Unreset the XMAC. */
	skge_write16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_CLR_MAC_RST);

	/*
	 * Perform additional initialization for external PHYs,
	 * namely for the 1000baseTX cards that use the XMAC's
	 * GMII mode.
	 */
	if (hw->phy_type != SK_PHY_XMAC) {
		/* Take external Phy out of reset */
		r = skge_read32(hw, B2_GP_IO);
		if (port == 0)
			r |= GP_DIR_0|GP_IO_0;
		else
			r |= GP_DIR_2|GP_IO_2;

		skge_write32(hw, B2_GP_IO, r);

		/* Enable GMII interface */
		xm_write16(hw, port, XM_HW_CFG, XM_HW_GMII_MD);
	}


	switch (hw->phy_type) {
	case SK_PHY_XMAC:
		xm_phy_init(skge);
		break;
	case SK_PHY_BCOM:
		bcom_phy_init(skge);
		bcom_check_link(hw, port);
	}

	/* Set Station Address */
	xm_outaddr(hw, port, XM_SA, dev->dev_addr);

	/* We don't use match addresses so clear */
	for (i = 1; i < 16; i++)
		xm_outaddr(hw, port, XM_EXM(i), zero);

	/* Clear MIB counters */
	xm_write16(hw, port, XM_STAT_CMD,
			XM_SC_CLR_RXC | XM_SC_CLR_TXC);
	/* Clear two times according to Errata #3 */
	xm_write16(hw, port, XM_STAT_CMD,
			XM_SC_CLR_RXC | XM_SC_CLR_TXC);

	/* configure Rx High Water Mark (XM_RX_HI_WM) */
	xm_write16(hw, port, XM_RX_HI_WM, 1450);

	/* We don't need the FCS appended to the packet. */
	r = XM_RX_LENERR_OK | XM_RX_STRIP_FCS;
	if (jumbo)
		r |= XM_RX_BIG_PK_OK;

	if (skge->duplex == DUPLEX_HALF) {
		/*
		 * If in manual half duplex mode the other side might be in
		 * full duplex mode, so ignore if a carrier extension is not seen
		 * on frames received
		 */
		r |= XM_RX_DIS_CEXT;
	}
	xm_write16(hw, port, XM_RX_CMD, r);

	/* We want short frames padded to 60 bytes. */
	xm_write16(hw, port, XM_TX_CMD, XM_TX_AUTO_PAD);

	/* Increase threshold for jumbo frames on dual port */
	if (hw->ports > 1 && jumbo)
		xm_write16(hw, port, XM_TX_THR, 1020);
	else
		xm_write16(hw, port, XM_TX_THR, 512);

	/*
	 * Enable the reception of all error frames. This is is
	 * a necessary evil due to the design of the XMAC. The
	 * XMAC's receive FIFO is only 8K in size, however jumbo
	 * frames can be up to 9000 bytes in length. When bad
	 * frame filtering is enabled, the XMAC's RX FIFO operates
	 * in 'store and forward' mode. For this to work, the
	 * entire frame has to fit into the FIFO, but that means
	 * that jumbo frames larger than 8192 bytes will be
	 * truncated. Disabling all bad frame filtering causes
	 * the RX FIFO to operate in streaming mode, in which
	 * case the XMAC will start transferring frames out of the
	 * RX FIFO as soon as the FIFO threshold is reached.
	 */
	xm_write32(hw, port, XM_MODE, XM_DEF_MODE);


	/*
	 * Initialize the Receive Counter Event Mask (XM_RX_EV_MSK)
	 *	- Enable all bits excepting 'Octets Rx OK Low CntOv'
	 *	  and 'Octets Rx OK Hi Cnt Ov'.
	 */
	xm_write32(hw, port, XM_RX_EV_MSK, XMR_DEF_MSK);

	/*
	 * Initialize the Transmit Counter Event Mask (XM_TX_EV_MSK)
	 *	- Enable all bits excepting 'Octets Tx OK Low CntOv'
	 *	  and 'Octets Tx OK Hi Cnt Ov'.
	 */
	xm_write32(hw, port, XM_TX_EV_MSK, XMT_DEF_MSK);

	/* Configure MAC arbiter */
	skge_write16(hw, B3_MA_TO_CTRL, MA_RST_CLR);

	/* configure timeout values */
	skge_write8(hw, B3_MA_TOINI_RX1, 72);
	skge_write8(hw, B3_MA_TOINI_RX2, 72);
	skge_write8(hw, B3_MA_TOINI_TX1, 72);
	skge_write8(hw, B3_MA_TOINI_TX2, 72);

	skge_write8(hw, B3_MA_RCINI_RX1, 0);
	skge_write8(hw, B3_MA_RCINI_RX2, 0);
	skge_write8(hw, B3_MA_RCINI_TX1, 0);
	skge_write8(hw, B3_MA_RCINI_TX2, 0);

	/* Configure Rx MAC FIFO */
	skge_write8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_RST_CLR);
	skge_write16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_TIM_PAT);
	skge_write8(hw, SK_REG(port, RX_MFF_CTRL2), MFF_ENA_OP_MD);

	/* Configure Tx MAC FIFO */
	skge_write8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_RST_CLR);
	skge_write16(hw, SK_REG(port, TX_MFF_CTRL1), MFF_TX_CTRL_DEF);
	skge_write8(hw, SK_REG(port, TX_MFF_CTRL2), MFF_ENA_OP_MD);

	if (jumbo) {
		/* Enable frame flushing if jumbo frames used */
		skge_write16(hw, SK_REG(port, RX_MFF_CTRL1), MFF_ENA_FLUSH);
	} else {
		/* enable timeout timers if normal frames */
		skge_write16(hw, B3_PA_CTRL,
			     (port == 0) ? PA_ENA_TO_TX1 : PA_ENA_TO_TX2);
	}
}