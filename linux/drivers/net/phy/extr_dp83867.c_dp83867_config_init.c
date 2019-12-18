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
typedef  int u16 ;
struct phy_device {scalar_t__ interface; struct dp83867_private* priv; } ;
struct dp83867_private {int fifo_depth; int rx_id_delay; int tx_id_delay; scalar_t__ io_impedance; scalar_t__ port_mirroring; int clk_output_sel; scalar_t__ set_clk_output; scalar_t__ sgmii_ref_clk_en; scalar_t__ rxctrl_strap_quirk; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DP83867_10M_SGMII_CFG ; 
 int DP83867_10M_SGMII_RATE_ADAPT_MASK ; 
 int /*<<< orphan*/  DP83867_CFG3 ; 
 int /*<<< orphan*/  DP83867_CFG4 ; 
 int DP83867_CFG4_SGMII_ANEG_MASK ; 
 int DP83867_CFG4_SGMII_ANEG_TIMER_16MS ; 
 int DP83867_CLK_O_SEL_OFF ; 
 int /*<<< orphan*/  DP83867_DEVADDR ; 
 int /*<<< orphan*/  DP83867_IO_MUX_CFG ; 
 int DP83867_IO_MUX_CFG_CLK_O_DISABLE ; 
 int DP83867_IO_MUX_CFG_CLK_O_SEL_MASK ; 
 int DP83867_IO_MUX_CFG_CLK_O_SEL_SHIFT ; 
 int DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK ; 
 int DP83867_PHYCR_FIFO_DEPTH_MASK ; 
 int DP83867_PHYCR_FIFO_DEPTH_SHIFT ; 
 int DP83867_PHYCR_RESERVED_MASK ; 
 scalar_t__ DP83867_PORT_MIRROING_KEEP ; 
 int /*<<< orphan*/  DP83867_RGMIICTL ; 
 int /*<<< orphan*/  DP83867_RGMIIDCTL ; 
 int DP83867_RGMII_RX_CLK_DELAY_EN ; 
 int DP83867_RGMII_TX_CLK_DELAY_EN ; 
 int DP83867_RGMII_TX_CLK_DELAY_SHIFT ; 
 int /*<<< orphan*/  DP83867_SGMIICTL ; 
 int DP83867_SGMII_TYPE ; 
 int /*<<< orphan*/  DP83867_STRAP_STS1 ; 
 int DP83867_STRAP_STS1_RESERVED ; 
 int /*<<< orphan*/  MII_DP83867_PHYCTRL ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_RXID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  dp83867_config_port_mirroring (struct phy_device*) ; 
 int dp83867_of_init (struct phy_device*) ; 
 int /*<<< orphan*/  phy_clear_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 
 scalar_t__ phy_interrupt_is_valid (struct phy_device*) ; 
 int phy_modify_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83867_config_init(struct phy_device *phydev)
{
	struct dp83867_private *dp83867 = phydev->priv;
	int ret, val, bs;
	u16 delay;

	ret = dp83867_of_init(phydev);
	if (ret)
		return ret;

	/* RX_DV/RX_CTRL strapped in mode 1 or mode 2 workaround */
	if (dp83867->rxctrl_strap_quirk)
		phy_clear_bits_mmd(phydev, DP83867_DEVADDR, DP83867_CFG4,
				   BIT(7));

	if (phy_interface_is_rgmii(phydev)) {
		val = phy_read(phydev, MII_DP83867_PHYCTRL);
		if (val < 0)
			return val;
		val &= ~DP83867_PHYCR_FIFO_DEPTH_MASK;
		val |= (dp83867->fifo_depth << DP83867_PHYCR_FIFO_DEPTH_SHIFT);

		/* The code below checks if "port mirroring" N/A MODE4 has been
		 * enabled during power on bootstrap.
		 *
		 * Such N/A mode enabled by mistake can put PHY IC in some
		 * internal testing mode and disable RGMII transmission.
		 *
		 * In this particular case one needs to check STRAP_STS1
		 * register's bit 11 (marked as RESERVED).
		 */

		bs = phy_read_mmd(phydev, DP83867_DEVADDR, DP83867_STRAP_STS1);
		if (bs & DP83867_STRAP_STS1_RESERVED)
			val &= ~DP83867_PHYCR_RESERVED_MASK;

		ret = phy_write(phydev, MII_DP83867_PHYCTRL, val);
		if (ret)
			return ret;

		/* If rgmii mode with no internal delay is selected, we do NOT use
		 * aligned mode as one might expect.  Instead we use the PHY's default
		 * based on pin strapping.  And the "mode 0" default is to *use*
		 * internal delay with a value of 7 (2.00 ns).
		 *
		 * Set up RGMII delays
		 */
		val = phy_read_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIICTL);

		val &= ~(DP83867_RGMII_TX_CLK_DELAY_EN | DP83867_RGMII_RX_CLK_DELAY_EN);
		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID)
			val |= (DP83867_RGMII_TX_CLK_DELAY_EN | DP83867_RGMII_RX_CLK_DELAY_EN);

		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
			val |= DP83867_RGMII_TX_CLK_DELAY_EN;

		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_RXID)
			val |= DP83867_RGMII_RX_CLK_DELAY_EN;

		phy_write_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIICTL, val);

		delay = (dp83867->rx_id_delay |
			(dp83867->tx_id_delay << DP83867_RGMII_TX_CLK_DELAY_SHIFT));

		phy_write_mmd(phydev, DP83867_DEVADDR, DP83867_RGMIIDCTL,
			      delay);
	}

	/* If specified, set io impedance */
	if (dp83867->io_impedance >= 0)
		phy_modify_mmd(phydev, DP83867_DEVADDR, DP83867_IO_MUX_CFG,
			       DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK,
			       dp83867->io_impedance);

	if (phydev->interface == PHY_INTERFACE_MODE_SGMII) {
		/* For support SPEED_10 in SGMII mode
		 * DP83867_10M_SGMII_RATE_ADAPT bit
		 * has to be cleared by software. That
		 * does not affect SPEED_100 and
		 * SPEED_1000.
		 */
		ret = phy_modify_mmd(phydev, DP83867_DEVADDR,
				     DP83867_10M_SGMII_CFG,
				     DP83867_10M_SGMII_RATE_ADAPT_MASK,
				     0);
		if (ret)
			return ret;

		/* After reset SGMII Autoneg timer is set to 2us (bits 6 and 5
		 * are 01). That is not enough to finalize autoneg on some
		 * devices. Increase this timer duration to maximum 16ms.
		 */
		ret = phy_modify_mmd(phydev, DP83867_DEVADDR,
				     DP83867_CFG4,
				     DP83867_CFG4_SGMII_ANEG_MASK,
				     DP83867_CFG4_SGMII_ANEG_TIMER_16MS);

		if (ret)
			return ret;

		val = phy_read_mmd(phydev, DP83867_DEVADDR, DP83867_SGMIICTL);
		/* SGMII type is set to 4-wire mode by default.
		 * If we place appropriate property in dts (see above)
		 * switch on 6-wire mode.
		 */
		if (dp83867->sgmii_ref_clk_en)
			val |= DP83867_SGMII_TYPE;
		else
			val &= ~DP83867_SGMII_TYPE;
		phy_write_mmd(phydev, DP83867_DEVADDR, DP83867_SGMIICTL, val);
	}

	/* Enable Interrupt output INT_OE in CFG3 register */
	if (phy_interrupt_is_valid(phydev)) {
		val = phy_read(phydev, DP83867_CFG3);
		val |= BIT(7);
		phy_write(phydev, DP83867_CFG3, val);
	}

	if (dp83867->port_mirroring != DP83867_PORT_MIRROING_KEEP)
		dp83867_config_port_mirroring(phydev);

	/* Clock output selection if muxing property is set */
	if (dp83867->set_clk_output) {
		u16 mask = DP83867_IO_MUX_CFG_CLK_O_DISABLE;

		if (dp83867->clk_output_sel == DP83867_CLK_O_SEL_OFF) {
			val = DP83867_IO_MUX_CFG_CLK_O_DISABLE;
		} else {
			mask |= DP83867_IO_MUX_CFG_CLK_O_SEL_MASK;
			val = dp83867->clk_output_sel <<
			      DP83867_IO_MUX_CFG_CLK_O_SEL_SHIFT;
		}

		phy_modify_mmd(phydev, DP83867_DEVADDR, DP83867_IO_MUX_CFG,
			       mask, val);
	}

	return 0;
}