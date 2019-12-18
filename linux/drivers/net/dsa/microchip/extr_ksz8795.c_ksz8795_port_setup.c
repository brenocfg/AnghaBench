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
struct TYPE_2__ {int duplex; scalar_t__ link; void* speed; } ;
struct ksz_port {int vid_member; TYPE_1__ phydev; } ;
struct ksz_device {int interface; int port_mask; int on_ports; int host_mask; int live_ports; struct ksz_port* ports; } ;

/* Variables and functions */
 int BIT (int) ; 
#define  PHY_INTERFACE_MODE_GMII 130 
#define  PHY_INTERFACE_MODE_MII 129 
 int PHY_INTERFACE_MODE_RGMII_ID ; 
 int PHY_INTERFACE_MODE_RGMII_RXID ; 
 int PHY_INTERFACE_MODE_RGMII_TXID ; 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  PORT_802_1P_ENABLE ; 
 int /*<<< orphan*/  PORT_802_1P_REMAPPING ; 
 int /*<<< orphan*/  PORT_BROADCAST_STORM ; 
 int /*<<< orphan*/  PORT_DIFFSERV_ENABLE ; 
 int PORT_GMII_1GPS_MODE ; 
 int PORT_INTERFACE_GMII ; 
 int PORT_INTERFACE_RGMII ; 
 int PORT_INTERFACE_RMII ; 
 int PORT_INTERFACE_TYPE ; 
 int PORT_RGMII_ID_IN_ENABLE ; 
 int PORT_RGMII_ID_OUT_ENABLE ; 
 int /*<<< orphan*/  P_802_1P_CTRL ; 
 int /*<<< orphan*/  P_BCAST_STORM_CTRL ; 
 int /*<<< orphan*/  P_PRIO_CTRL ; 
 int /*<<< orphan*/  REG_PORT_5_CTRL_6 ; 
 void* SPEED_100 ; 
 void* SPEED_1000 ; 
 int /*<<< orphan*/  ksz8795_cfg_port_member (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  ksz8795_set_prio_queue (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ksz8795_port_setup(struct ksz_device *dev, int port, bool cpu_port)
{
	struct ksz_port *p = &dev->ports[port];
	u8 data8, member;

	/* enable broadcast storm limit */
	ksz_port_cfg(dev, port, P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, true);

	ksz8795_set_prio_queue(dev, port, 4);

	/* disable DiffServ priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_DIFFSERV_ENABLE, false);

	/* replace priority */
	ksz_port_cfg(dev, port, P_802_1P_CTRL, PORT_802_1P_REMAPPING, false);

	/* enable 802.1p priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_802_1P_ENABLE, true);

	if (cpu_port) {
		/* Configure MII interface for proper network communication. */
		ksz_read8(dev, REG_PORT_5_CTRL_6, &data8);
		data8 &= ~PORT_INTERFACE_TYPE;
		data8 &= ~PORT_GMII_1GPS_MODE;
		switch (dev->interface) {
		case PHY_INTERFACE_MODE_MII:
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_RMII:
			data8 |= PORT_INTERFACE_RMII;
			p->phydev.speed = SPEED_100;
			break;
		case PHY_INTERFACE_MODE_GMII:
			data8 |= PORT_GMII_1GPS_MODE;
			data8 |= PORT_INTERFACE_GMII;
			p->phydev.speed = SPEED_1000;
			break;
		default:
			data8 &= ~PORT_RGMII_ID_IN_ENABLE;
			data8 &= ~PORT_RGMII_ID_OUT_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_RXID)
				data8 |= PORT_RGMII_ID_IN_ENABLE;
			if (dev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
			    dev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
				data8 |= PORT_RGMII_ID_OUT_ENABLE;
			data8 |= PORT_GMII_1GPS_MODE;
			data8 |= PORT_INTERFACE_RGMII;
			p->phydev.speed = SPEED_1000;
			break;
		}
		ksz_write8(dev, REG_PORT_5_CTRL_6, data8);
		p->phydev.duplex = 1;

		member = dev->port_mask;
		dev->on_ports = dev->host_mask;
		dev->live_ports = dev->host_mask;
	} else {
		member = dev->host_mask | p->vid_member;
		dev->on_ports |= BIT(port);

		/* Link was detected before port is enabled. */
		if (p->phydev.link)
			dev->live_ports |= BIT(port);
	}
	ksz8795_cfg_port_member(dev, port, member);
}