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
typedef  int /*<<< orphan*/  u8 ;
struct ocelot_port {int /*<<< orphan*/  chip_port; struct ocelot* ocelot; } ;
struct ocelot {int shared_queue_sz; } ;
struct net_device {TYPE_1__* phydev; } ;
struct TYPE_2__ {int speed; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PFC_PFC_CFG ; 
 int /*<<< orphan*/  ANA_PFC_PFC_CFG_FC_LINK_SPEED (int) ; 
 int /*<<< orphan*/  ANA_POL_FLOWC ; 
 int /*<<< orphan*/  DEV_CLOCK_CFG ; 
 int DEV_CLOCK_CFG_LINK_SPEED (int) ; 
 int /*<<< orphan*/  DEV_MAC_ENA_CFG ; 
 int DEV_MAC_ENA_CFG_RX_ENA ; 
 int DEV_MAC_ENA_CFG_TX_ENA ; 
 int /*<<< orphan*/  DEV_MAC_FC_MAC_HIGH_CFG ; 
 int /*<<< orphan*/  DEV_MAC_FC_MAC_LOW_CFG ; 
 int /*<<< orphan*/  DEV_MAC_HDX_CFG ; 
 int DEV_MAC_HDX_CFG_LATE_COL_POS (int) ; 
 int DEV_MAC_HDX_CFG_SEED_LOAD ; 
 int /*<<< orphan*/  DEV_MAC_IFG_CFG ; 
 int DEV_MAC_IFG_CFG_TX_IFG (int) ; 
 int /*<<< orphan*/  DEV_MAC_MAXLEN_CFG ; 
 int /*<<< orphan*/  DEV_MAC_MODE_CFG ; 
 int DEV_MAC_MODE_CFG_FDX_ENA ; 
 int DEV_MAC_MODE_CFG_GIGA_MODE_ENA ; 
 int /*<<< orphan*/  DEV_MAC_TAGS_CFG ; 
 int DEV_MAC_TAGS_CFG_TAG_ID (int /*<<< orphan*/ ) ; 
 int DEV_MAC_TAGS_CFG_VLAN_AWR_ENA ; 
 int DEV_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA ; 
 int /*<<< orphan*/  DEV_PORT_MISC ; 
 int DEV_PORT_MISC_HDX_FAST_DIS ; 
 int /*<<< orphan*/  ETH_P_8021AD ; 
 int OCELOT_BUFFER_CELL_SZ ; 
 int OCELOT_SPEED_10 ; 
 int OCELOT_SPEED_100 ; 
 int OCELOT_SPEED_1000 ; 
 int OCELOT_SPEED_2500 ; 
 int /*<<< orphan*/  PCS1G_ANEG_CFG ; 
 int /*<<< orphan*/  PCS1G_CFG ; 
 int PCS1G_CFG_PCS_ENA ; 
 int /*<<< orphan*/  PCS1G_LB_CFG ; 
 int /*<<< orphan*/  PCS1G_MODE_CFG ; 
 int PCS1G_MODE_CFG_SGMII_MODE_ENA ; 
 int /*<<< orphan*/  PCS1G_SD_CFG ; 
 int PCS1G_SD_CFG_SD_SEL ; 
 int /*<<< orphan*/  QSYS_SWITCH_PORT_MODE ; 
 int QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE ; 
 int QSYS_SWITCH_PORT_MODE_PORT_ENA ; 
 int QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG (int) ; 
#define  SPEED_10 131 
#define  SPEED_100 130 
#define  SPEED_1000 129 
#define  SPEED_2500 128 
 int /*<<< orphan*/  SYS_ATOP ; 
 int /*<<< orphan*/  SYS_ATOP_TOT_CFG ; 
 int /*<<< orphan*/  SYS_MAC_FC_CFG ; 
 int SYS_MAC_FC_CFG_FC_LATENCY_CFG (int) ; 
 int SYS_MAC_FC_CFG_FC_LINK_SPEED (int) ; 
 int SYS_MAC_FC_CFG_PAUSE_VAL_CFG (int) ; 
 int SYS_MAC_FC_CFG_RX_FC_ENA ; 
 int SYS_MAC_FC_CFG_TX_FC_ENA ; 
 int SYS_MAC_FC_CFG_ZERO_PAUSE_ENA ; 
 int /*<<< orphan*/  SYS_PAUSE_CFG ; 
 int SYS_PAUSE_CFG_PAUSE_ENA ; 
 int SYS_PAUSE_CFG_PAUSE_START (int) ; 
 int SYS_PAUSE_CFG_PAUSE_STOP (int) ; 
 int VLAN_ETH_FRAME_LEN ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ocelot_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ocelot_port_writel (struct ocelot_port*,int,int /*<<< orphan*/ ) ; 
 int ocelot_wm_enc (int) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write_rix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_print_status (TYPE_1__*) ; 

__attribute__((used)) static void ocelot_port_adjust_link(struct net_device *dev)
{
	struct ocelot_port *port = netdev_priv(dev);
	struct ocelot *ocelot = port->ocelot;
	u8 p = port->chip_port;
	int speed, atop_wm, mode = 0;

	switch (dev->phydev->speed) {
	case SPEED_10:
		speed = OCELOT_SPEED_10;
		break;
	case SPEED_100:
		speed = OCELOT_SPEED_100;
		break;
	case SPEED_1000:
		speed = OCELOT_SPEED_1000;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA;
		break;
	case SPEED_2500:
		speed = OCELOT_SPEED_2500;
		mode = DEV_MAC_MODE_CFG_GIGA_MODE_ENA;
		break;
	default:
		netdev_err(dev, "Unsupported PHY speed: %d\n",
			   dev->phydev->speed);
		return;
	}

	phy_print_status(dev->phydev);

	if (!dev->phydev->link)
		return;

	/* Only full duplex supported for now */
	ocelot_port_writel(port, DEV_MAC_MODE_CFG_FDX_ENA |
			   mode, DEV_MAC_MODE_CFG);

	/* Set MAC IFG Gaps
	 * FDX: TX_IFG = 5, RX_IFG1 = RX_IFG2 = 0
	 * !FDX: TX_IFG = 5, RX_IFG1 = RX_IFG2 = 5
	 */
	ocelot_port_writel(port, DEV_MAC_IFG_CFG_TX_IFG(5), DEV_MAC_IFG_CFG);

	/* Load seed (0) and set MAC HDX late collision  */
	ocelot_port_writel(port, DEV_MAC_HDX_CFG_LATE_COL_POS(67) |
			   DEV_MAC_HDX_CFG_SEED_LOAD,
			   DEV_MAC_HDX_CFG);
	mdelay(1);
	ocelot_port_writel(port, DEV_MAC_HDX_CFG_LATE_COL_POS(67),
			   DEV_MAC_HDX_CFG);

	/* Disable HDX fast control */
	ocelot_port_writel(port, DEV_PORT_MISC_HDX_FAST_DIS, DEV_PORT_MISC);

	/* SGMII only for now */
	ocelot_port_writel(port, PCS1G_MODE_CFG_SGMII_MODE_ENA, PCS1G_MODE_CFG);
	ocelot_port_writel(port, PCS1G_SD_CFG_SD_SEL, PCS1G_SD_CFG);

	/* Enable PCS */
	ocelot_port_writel(port, PCS1G_CFG_PCS_ENA, PCS1G_CFG);

	/* No aneg on SGMII */
	ocelot_port_writel(port, 0, PCS1G_ANEG_CFG);

	/* No loopback */
	ocelot_port_writel(port, 0, PCS1G_LB_CFG);

	/* Set Max Length and maximum tags allowed */
	ocelot_port_writel(port, VLAN_ETH_FRAME_LEN, DEV_MAC_MAXLEN_CFG);
	ocelot_port_writel(port, DEV_MAC_TAGS_CFG_TAG_ID(ETH_P_8021AD) |
			   DEV_MAC_TAGS_CFG_VLAN_AWR_ENA |
			   DEV_MAC_TAGS_CFG_VLAN_LEN_AWR_ENA,
			   DEV_MAC_TAGS_CFG);

	/* Enable MAC module */
	ocelot_port_writel(port, DEV_MAC_ENA_CFG_RX_ENA |
			   DEV_MAC_ENA_CFG_TX_ENA, DEV_MAC_ENA_CFG);

	/* Take MAC, Port, Phy (intern) and PCS (SGMII/Serdes) clock out of
	 * reset */
	ocelot_port_writel(port, DEV_CLOCK_CFG_LINK_SPEED(speed),
			   DEV_CLOCK_CFG);

	/* Set SMAC of Pause frame (00:00:00:00:00:00) */
	ocelot_port_writel(port, 0, DEV_MAC_FC_MAC_HIGH_CFG);
	ocelot_port_writel(port, 0, DEV_MAC_FC_MAC_LOW_CFG);

	/* No PFC */
	ocelot_write_gix(ocelot, ANA_PFC_PFC_CFG_FC_LINK_SPEED(speed),
			 ANA_PFC_PFC_CFG, p);

	/* Set Pause WM hysteresis
	 * 152 = 6 * VLAN_ETH_FRAME_LEN / OCELOT_BUFFER_CELL_SZ
	 * 101 = 4 * VLAN_ETH_FRAME_LEN / OCELOT_BUFFER_CELL_SZ
	 */
	ocelot_write_rix(ocelot, SYS_PAUSE_CFG_PAUSE_ENA |
			 SYS_PAUSE_CFG_PAUSE_STOP(101) |
			 SYS_PAUSE_CFG_PAUSE_START(152), SYS_PAUSE_CFG, p);

	/* Core: Enable port for frame transfer */
	ocelot_write_rix(ocelot, QSYS_SWITCH_PORT_MODE_INGRESS_DROP_MODE |
			 QSYS_SWITCH_PORT_MODE_SCH_NEXT_CFG(1) |
			 QSYS_SWITCH_PORT_MODE_PORT_ENA,
			 QSYS_SWITCH_PORT_MODE, p);

	/* Flow control */
	ocelot_write_rix(ocelot, SYS_MAC_FC_CFG_PAUSE_VAL_CFG(0xffff) |
			 SYS_MAC_FC_CFG_RX_FC_ENA | SYS_MAC_FC_CFG_TX_FC_ENA |
			 SYS_MAC_FC_CFG_ZERO_PAUSE_ENA |
			 SYS_MAC_FC_CFG_FC_LATENCY_CFG(0x7) |
			 SYS_MAC_FC_CFG_FC_LINK_SPEED(speed),
			 SYS_MAC_FC_CFG, p);
	ocelot_write_rix(ocelot, 0, ANA_POL_FLOWC, p);

	/* Tail dropping watermark */
	atop_wm = (ocelot->shared_queue_sz - 9 * VLAN_ETH_FRAME_LEN) / OCELOT_BUFFER_CELL_SZ;
	ocelot_write_rix(ocelot, ocelot_wm_enc(9 * VLAN_ETH_FRAME_LEN),
			 SYS_ATOP, p);
	ocelot_write(ocelot, ocelot_wm_enc(atop_wm), SYS_ATOP_TOT_CFG);
}