#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct phy_device {scalar_t__ duplex; int speed; scalar_t__ interface; scalar_t__ asym_pause; scalar_t__ pause; scalar_t__ link; } ;
struct ethtool_eee {int /*<<< orphan*/  eee_enabled; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct b53_device* priv; } ;
struct b53_device {int cpu_port; TYPE_1__* ports; } ;
struct TYPE_2__ {struct ethtool_eee eee; } ;

/* Variables and functions */
 int /*<<< orphan*/  B53_CTRL_PAGE ; 
 int B53_GMII_PORT_OVERRIDE_CTRL (int) ; 
 int B53_PORT_OVERRIDE_CTRL ; 
 int B53_RGMII_CTRL_IMP ; 
 int B53_RGMII_CTRL_P (int) ; 
 scalar_t__ DUPLEX_FULL ; 
 int GMII_PO_EN ; 
 int GMII_PO_LINK ; 
 int GMII_PO_RX_FLOW ; 
 int GMII_PO_SPEED_2000M ; 
 int GMII_PO_TX_FLOW ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int PORT_OVERRIDE_EN ; 
 int PORT_OVERRIDE_FULL_DUPLEX ; 
 int PORT_OVERRIDE_LINK ; 
 int PORT_OVERRIDE_RV_MII_25 ; 
 int PORT_OVERRIDE_RX_FLOW ; 
 int PORT_OVERRIDE_SPEED_1000M ; 
 int PORT_OVERRIDE_SPEED_100M ; 
 int PORT_OVERRIDE_SPEED_10M ; 
 int PORT_OVERRIDE_SPEED_2000M ; 
 int PORT_OVERRIDE_TX_FLOW ; 
 int RGMII_CTRL_DLL_RXC ; 
 int RGMII_CTRL_DLL_TXC ; 
 int RGMII_CTRL_TIMING_SEL ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  b53_eee_init (struct dsa_switch*,int,struct phy_device*) ; 
 int /*<<< orphan*/  b53_read8 (struct b53_device*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  b53_write8 (struct b53_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is5301x (struct b53_device*) ; 
 scalar_t__ is531x5 (struct b53_device*) ; 
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ phy_interface_is_rgmii (struct phy_device*) ; 
 int /*<<< orphan*/  phy_is_pseudo_fixed_link (struct phy_device*) ; 
 int /*<<< orphan*/  phy_modes (scalar_t__) ; 

__attribute__((used)) static void b53_adjust_link(struct dsa_switch *ds, int port,
			    struct phy_device *phydev)
{
	struct b53_device *dev = ds->priv;
	struct ethtool_eee *p = &dev->ports[port].eee;
	u8 rgmii_ctrl = 0, reg = 0, off;

	if (!phy_is_pseudo_fixed_link(phydev))
		return;

	/* Override the port settings */
	if (port == dev->cpu_port) {
		off = B53_PORT_OVERRIDE_CTRL;
		reg = PORT_OVERRIDE_EN;
	} else {
		off = B53_GMII_PORT_OVERRIDE_CTRL(port);
		reg = GMII_PO_EN;
	}

	/* Set the link UP */
	if (phydev->link)
		reg |= PORT_OVERRIDE_LINK;

	if (phydev->duplex == DUPLEX_FULL)
		reg |= PORT_OVERRIDE_FULL_DUPLEX;

	switch (phydev->speed) {
	case 2000:
		reg |= PORT_OVERRIDE_SPEED_2000M;
		/* fallthrough */
	case SPEED_1000:
		reg |= PORT_OVERRIDE_SPEED_1000M;
		break;
	case SPEED_100:
		reg |= PORT_OVERRIDE_SPEED_100M;
		break;
	case SPEED_10:
		reg |= PORT_OVERRIDE_SPEED_10M;
		break;
	default:
		dev_err(ds->dev, "unknown speed: %d\n", phydev->speed);
		return;
	}

	/* Enable flow control on BCM5301x's CPU port */
	if (is5301x(dev) && port == dev->cpu_port)
		reg |= PORT_OVERRIDE_RX_FLOW | PORT_OVERRIDE_TX_FLOW;

	if (phydev->pause) {
		if (phydev->asym_pause)
			reg |= PORT_OVERRIDE_TX_FLOW;
		reg |= PORT_OVERRIDE_RX_FLOW;
	}

	b53_write8(dev, B53_CTRL_PAGE, off, reg);

	if (is531x5(dev) && phy_interface_is_rgmii(phydev)) {
		if (port == 8)
			off = B53_RGMII_CTRL_IMP;
		else
			off = B53_RGMII_CTRL_P(port);

		/* Configure the port RGMII clock delay by DLL disabled and
		 * tx_clk aligned timing (restoring to reset defaults)
		 */
		b53_read8(dev, B53_CTRL_PAGE, off, &rgmii_ctrl);
		rgmii_ctrl &= ~(RGMII_CTRL_DLL_RXC | RGMII_CTRL_DLL_TXC |
				RGMII_CTRL_TIMING_SEL);

		/* PHY_INTERFACE_MODE_RGMII_TXID means TX internal delay, make
		 * sure that we enable the port TX clock internal delay to
		 * account for this internal delay that is inserted, otherwise
		 * the switch won't be able to receive correctly.
		 *
		 * PHY_INTERFACE_MODE_RGMII means that we are not introducing
		 * any delay neither on transmission nor reception, so the
		 * BCM53125 must also be configured accordingly to account for
		 * the lack of delay and introduce
		 *
		 * The BCM53125 switch has its RX clock and TX clock control
		 * swapped, hence the reason why we modify the TX clock path in
		 * the "RGMII" case
		 */
		if (phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
			rgmii_ctrl |= RGMII_CTRL_DLL_TXC;
		if (phydev->interface == PHY_INTERFACE_MODE_RGMII)
			rgmii_ctrl |= RGMII_CTRL_DLL_TXC | RGMII_CTRL_DLL_RXC;
		rgmii_ctrl |= RGMII_CTRL_TIMING_SEL;
		b53_write8(dev, B53_CTRL_PAGE, off, rgmii_ctrl);

		dev_info(ds->dev, "Configured port %d for %s\n", port,
			 phy_modes(phydev->interface));
	}

	/* configure MII port if necessary */
	if (is5325(dev)) {
		b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
			  &reg);

		/* reverse mii needs to be enabled */
		if (!(reg & PORT_OVERRIDE_RV_MII_25)) {
			b53_write8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				   reg | PORT_OVERRIDE_RV_MII_25);
			b53_read8(dev, B53_CTRL_PAGE, B53_PORT_OVERRIDE_CTRL,
				  &reg);

			if (!(reg & PORT_OVERRIDE_RV_MII_25)) {
				dev_err(ds->dev,
					"Failed to enable reverse MII mode\n");
				return;
			}
		}
	} else if (is5301x(dev)) {
		if (port != dev->cpu_port) {
			u8 po_reg = B53_GMII_PORT_OVERRIDE_CTRL(dev->cpu_port);
			u8 gmii_po;

			b53_read8(dev, B53_CTRL_PAGE, po_reg, &gmii_po);
			gmii_po |= GMII_PO_LINK |
				   GMII_PO_RX_FLOW |
				   GMII_PO_TX_FLOW |
				   GMII_PO_EN |
				   GMII_PO_SPEED_2000M;
			b53_write8(dev, B53_CTRL_PAGE, po_reg, gmii_po);
		}
	}

	/* Re-negotiate EEE if it was enabled already */
	p->eee_enabled = b53_eee_init(ds, port, phydev);
}