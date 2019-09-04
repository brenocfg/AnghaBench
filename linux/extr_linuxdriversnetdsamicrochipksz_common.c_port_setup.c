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
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTI_PVID_REPLACE ; 
 int PORT_802_1P_PRIO_ENABLE ; 
 int PORT_BACK_PRESSURE ; 
 int PORT_BROADCAST_STORM ; 
 int PORT_DIFFSERV_PRIO_ENABLE ; 
 int PORT_FORCE_RX_FLOW_CTRL ; 
 int PORT_FORCE_TX_FLOW_CTRL ; 
 int PORT_MAC_LOOPBACK ; 
 int /*<<< orphan*/  PORT_MII_NOT_1GBIT ; 
 int /*<<< orphan*/  PORT_MII_SEL_M ; 
 int /*<<< orphan*/  PORT_RGMII_ID_EG_ENABLE ; 
 int /*<<< orphan*/  PORT_RGMII_SEL ; 
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
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ksz_port_cfg32 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_pread16 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_pwrite8 (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void port_setup(struct ksz_device *dev, int port, bool cpu_port)
{
	u8 data8;
	u16 data16;

	/* enable tag tail for host port */
	if (cpu_port)
		ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_TAIL_TAG_ENABLE,
			     true);

	ksz_port_cfg(dev, port, REG_PORT_CTRL_0, PORT_MAC_LOOPBACK, false);

	/* set back pressure */
	ksz_port_cfg(dev, port, REG_PORT_MAC_CTRL_1, PORT_BACK_PRESSURE, true);

	/* set flow control */
	ksz_port_cfg(dev, port, REG_PORT_CTRL_0,
		     PORT_FORCE_TX_FLOW_CTRL | PORT_FORCE_RX_FLOW_CTRL, true);

	/* enable broadcast storm limit */
	ksz_port_cfg(dev, port, P_BCAST_STORM_CTRL, PORT_BROADCAST_STORM, true);

	/* disable DiffServ priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_DIFFSERV_PRIO_ENABLE, false);

	/* replace priority */
	ksz_port_cfg(dev, port, REG_PORT_MRI_MAC_CTRL, PORT_USER_PRIO_CEILING,
		     false);
	ksz_port_cfg32(dev, port, REG_PORT_MTI_QUEUE_CTRL_0__4,
		       MTI_PVID_REPLACE, false);

	/* enable 802.1p priority */
	ksz_port_cfg(dev, port, P_PRIO_CTRL, PORT_802_1P_PRIO_ENABLE, true);

	/* configure MAC to 1G & RGMII mode */
	ksz_pread8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
	data8 |= PORT_RGMII_ID_EG_ENABLE;
	data8 &= ~PORT_MII_NOT_1GBIT;
	data8 &= ~PORT_MII_SEL_M;
	data8 |= PORT_RGMII_SEL;
	ksz_pwrite8(dev, port, REG_PORT_XMII_CTRL_1, data8);

	/* clear pending interrupts */
	ksz_pread16(dev, port, REG_PORT_PHY_INT_ENABLE, &data16);
}