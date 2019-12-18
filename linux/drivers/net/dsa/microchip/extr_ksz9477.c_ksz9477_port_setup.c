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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int duplex; scalar_t__ link; void* speed; } ;
struct ksz_port {int vid_member; TYPE_1__ phydev; } ;
struct ksz_device {int phy_port_cnt; int interface; int port_mask; int on_ports; int host_mask; int live_ports; int /*<<< orphan*/  dev_mutex; scalar_t__ phy_errata_9477; struct ksz_port* ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTI_PVID_REPLACE ; 
#define  PHY_INTERFACE_MODE_GMII 130 
#define  PHY_INTERFACE_MODE_MII 129 
 int PHY_INTERFACE_MODE_RGMII_ID ; 
 int PHY_INTERFACE_MODE_RGMII_RXID ; 
 int PHY_INTERFACE_MODE_RGMII_TXID ; 
#define  PHY_INTERFACE_MODE_RMII 128 
 int PORT_802_1P_PRIO_ENABLE ; 
 int PORT_BACK_PRESSURE ; 
 int PORT_BROADCAST_STORM ; 
 int PORT_DIFFSERV_PRIO_ENABLE ; 
 int PORT_FORCE_RX_FLOW_CTRL ; 
 int PORT_FORCE_TX_FLOW_CTRL ; 
 int PORT_MAC_LOOPBACK ; 
 int PORT_RGMII_ID_EG_ENABLE ; 
 int PORT_RGMII_ID_IG_ENABLE ; 
 int PORT_TAIL_TAG_ENABLE ; 
 int PORT_USER_PRIO_CEILING ; 
 int /*<<< orphan*/  P_BCAST_STORM_CTRL ; 
 int /*<<< orphan*/  P_PRIO_CTRL ; 
 int /*<<< orphan*/  REG_PORT_CTRL_0 ; 
 int /*<<< orphan*/  REG_PORT_MAC_CTRL_1 ; 
 int /*<<< orphan*/  REG_PORT_MRI_MAC_CTRL ; 
 int /*<<< orphan*/  REG_PORT_MTI_QUEUE_CTRL_0__4 ; 
 int /*<<< orphan*/  REG_PORT_PHY_INT_ENABLE ; 
 int /*<<< orphan*/  REG_PORT_XMII_CTRL_1 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int /*<<< orphan*/  ksz9477_cfg_port_member (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  ksz9477_phy_errata_setup (struct ksz_device*,int) ; 
 int /*<<< orphan*/  ksz9477_port_cfg32 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz9477_set_gbit (struct ksz_device*,int,int*) ; 
 int /*<<< orphan*/  ksz9477_set_xmii (struct ksz_device*,int,int*) ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ksz_pread16 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ksz9477_port_setup(struct ksz_device *dev, int port, bool cpu_port)
{
	u8 data8;
	u8 member;
	u16 data16;
	struct ksz_port *p = &dev->ports[port];

	/* enable tag tail for host port */
	if (cpu_port)
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE,
			     true);

	ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, false);

	/* set back pressure */
	ksz_port_cfg(dev, port, REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, true);

	/* enable broadcast storm limit */
	ksz_port_cfg(dev, port, P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, true);

	/* disable DiffServ priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, false);

	/* replace priority */
	ksz_port_cfg(dev, port, REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING,
		     false);
	ksz9477_port_cfg32(dev, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
			   MTI_PVID_REPLACE, false);

	/* enable 802.1p priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, true);

	if (port < dev->phy_port_cnt) {
		/* do not force flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     false);

		if (dev->phy_errata_9477)
			ksz9477_phy_errata_setup(dev, port);
	} else {
		/* force flow control */
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
			     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL,
			     true);

		/* configure MAC to 1G & RGMII mode */
		ksz_pread8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
		switch (dev->interface) {
		case PHY_INTERFACE_MODE_MII:
			ksz9477_set_xmii(dev, 0, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_RMII:
			ksz9477_set_xmii(dev, 1, &data8);
			ksz9477_set_gbit(dev, false, &data8);
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_GMII:
			ksz9477_set_xmii(dev, 2, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			p->phydev.speed = SPEED_1000;
			break;
		default:
			ksz9477_set_xmii(dev, 3, &data8);
			ksz9477_set_gbit(dev, true, &data8);
			data8 &= ~PORT_RGMII_ID_IG_ENABLE;
			data8 &= ~PORT_RGMII_ID_EG_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_RXID)
				data8 |= PORT_RGMII_ID_IG_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
				data8 |= PORT_RGMII_ID_EG_ENABLE;
			p->phydev.speed = SPEED_1000;
			break;
		}
		ksz_pwrite8(dev, port, REG_PORT_XMII_CTRL_1, data8);
		p->phydev.duplex = 1;
	}
	mutex_lock(&dev->dev_mutex);
	if (cpu_port) {
		member = dev->port_mask;
		dev->on_ports = dev->host_mask;
		dev->live_ports = dev->host_mask;
	} else {
		member = dev->host_mask | p->vid_member;
		dev->on_ports |= (1 << port);

		/* Link was detected before port is enabled. */
		if (p->phydev.link)
			dev->live_ports |= (1 << port);
	}
	mutex_unlock(&dev->dev_mutex);
	ksz9477_cfg_port_member(dev, port, member);

	/* clear pending interrupts */
	if (port < dev->phy_port_cnt)
		ksz_pread16(dev, port, REG_PORT_PHY_INT_ENABLE, &data16);
}