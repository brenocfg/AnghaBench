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
typedef  int u8 ;
struct mt7530_priv {int p5_intf_sel; int /*<<< orphan*/  reg_mutex; scalar_t__ p5_interface; int /*<<< orphan*/  ds; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mt7530_priv* priv; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int CSR_RGMII_EDGE_ALIGN ; 
 int CSR_RGMII_TXC_CFG (int) ; 
 int MHWTRAP_MANUAL ; 
 int MHWTRAP_P5_DIS ; 
 int MHWTRAP_P5_MAC_SEL ; 
 int MHWTRAP_P5_RGMII_MODE ; 
 int MHWTRAP_PHY0_SEL ; 
 int /*<<< orphan*/  MT7530_IO_DRV_CR ; 
 int /*<<< orphan*/  MT7530_MHWTRAP ; 
 int /*<<< orphan*/  MT7530_P5RGMIIRXCR ; 
 int /*<<< orphan*/  MT7530_P5RGMIITXCR ; 
 int /*<<< orphan*/  MT7530_PMCR_P (int) ; 
#define  P5_DISABLED 131 
#define  P5_INTF_SEL_GMAC5 130 
#define  P5_INTF_SEL_PHY_P0 129 
#define  P5_INTF_SEL_PHY_P4 128 
 int P5_IO_CLK_DRV (int) ; 
 int P5_IO_DATA_DRV (int) ; 
 scalar_t__ PHY_INTERFACE_MODE_NA ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dsa_is_dsa_port (int /*<<< orphan*/ ,int) ; 
 int mt7530_read (struct mt7530_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt7530_write (struct mt7530_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p5_intf_modes (int) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  phy_modes (scalar_t__) ; 

__attribute__((used)) static void mt7530_setup_port5(struct dsa_switch *ds, phy_interface_t interface)
{
	struct mt7530_priv *priv = ds->priv;
	u8 tx_delay = 0;
	int val;

	mutex_lock(&priv->reg_mutex);

	val = mt7530_read(priv, MT7530_MHWTRAP);

	val |= MHWTRAP_MANUAL | MHWTRAP_P5_MAC_SEL | MHWTRAP_P5_DIS;
	val &= ~MHWTRAP_P5_RGMII_MODE & ~MHWTRAP_PHY0_SEL;

	switch (priv->p5_intf_sel) {
	case P5_INTF_SEL_PHY_P0:
		/* MT7530_P5_MODE_GPHY_P0: 2nd GMAC -> P5 -> P0 */
		val |= MHWTRAP_PHY0_SEL;
		/* fall through */
	case P5_INTF_SEL_PHY_P4:
		/* MT7530_P5_MODE_GPHY_P4: 2nd GMAC -> P5 -> P4 */
		val &= ~MHWTRAP_P5_MAC_SEL & ~MHWTRAP_P5_DIS;

		/* Setup the MAC by default for the cpu port */
		mt7530_write(priv, MT7530_PMCR_P(5), 0x56300);
		break;
	case P5_INTF_SEL_GMAC5:
		/* MT7530_P5_MODE_GMAC: P5 -> External phy or 2nd GMAC */
		val &= ~MHWTRAP_P5_DIS;
		break;
	case P5_DISABLED:
		interface = PHY_INTERFACE_MODE_NA;
		break;
	default:
		dev_err(ds->dev, "Unsupported p5_intf_sel %d\n",
			priv->p5_intf_sel);
		goto unlock_exit;
	}

	/* Setup RGMII settings */
	if (phy_interface_mode_is_rgmii(interface)) {
		val |= MHWTRAP_P5_RGMII_MODE;

		/* P5 RGMII RX Clock Control: delay setting for 1000M */
		mt7530_write(priv, MT7530_P5RGMIIRXCR, CSR_RGMII_EDGE_ALIGN);

		/* Don't set delay in DSA mode */
		if (!dsa_is_dsa_port(priv->ds, 5) &&
		    (interface == PHY_INTERFACE_MODE_RGMII_TXID ||
		     interface == PHY_INTERFACE_MODE_RGMII_ID))
			tx_delay = 4; /* n * 0.5 ns */

		/* P5 RGMII TX Clock Control: delay x */
		mt7530_write(priv, MT7530_P5RGMIITXCR,
			     CSR_RGMII_TXC_CFG(0x10 + tx_delay));

		/* reduce P5 RGMII Tx driving, 8mA */
		mt7530_write(priv, MT7530_IO_DRV_CR,
			     P5_IO_CLK_DRV(1) | P5_IO_DATA_DRV(1));
	}

	mt7530_write(priv, MT7530_MHWTRAP, val);

	dev_dbg(ds->dev, "Setup P5, HWTRAP=0x%x, intf_sel=%s, phy-mode=%s\n",
		val, p5_intf_modes(priv->p5_intf_sel), phy_modes(interface));

	priv->p5_interface = interface;

unlock_exit:
	mutex_unlock(&priv->reg_mutex);
}