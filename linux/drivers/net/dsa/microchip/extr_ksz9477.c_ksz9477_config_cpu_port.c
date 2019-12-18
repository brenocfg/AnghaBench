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
struct ksz_port {int vid_member; int on; int member; int phy; int sgmii; } ;
struct ksz_device {int port_cnt; int cpu_ports; int cpu_port; int host_mask; int port_mask; scalar_t__ interface; int member; int mib_port_cnt; int phy_port_cnt; int chip_id; struct ksz_port* ports; int /*<<< orphan*/  dev; } ;
struct dsa_switch {int num_ports; struct ksz_device* priv; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  BR_STATE_DISABLED ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 scalar_t__ ksz9477_get_interface (struct ksz_device*,int) ; 
 int /*<<< orphan*/  ksz9477_port_setup (struct ksz_device*,int,int) ; 
 int /*<<< orphan*/  ksz9477_port_stp_state_set (struct dsa_switch*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_modes (scalar_t__) ; 

__attribute__((used)) static void ksz9477_config_cpu_port(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	struct ksz_port *p;
	int i;

	ds->num_ports = dev->port_cnt;

	for (i = 0; i < dev->port_cnt; i++) {
		if (dsa_is_cpu_port(ds, i) && (dev->cpu_ports & (1 << i))) {
			phy_interface_t interface;

			dev->cpu_port = i;
			dev->host_mask = (1 << dev->cpu_port);
			dev->port_mask |= dev->host_mask;

			/* Read from XMII register to determine host port
			 * interface.  If set specifically in device tree
			 * note the difference to help debugging.
			 */
			interface = ksz9477_get_interface(dev, i);
			if (!dev->interface)
				dev->interface = interface;
			if (interface && interface != dev->interface)
				dev_info(dev->dev,
					 "use %s instead of %s\n",
					  phy_modes(dev->interface),
					  phy_modes(interface));

			/* enable cpu port */
			ksz9477_port_setup(dev, i, true);
			p = &dev->ports[dev->cpu_port];
			p->vid_member = dev->port_mask;
			p->on = 1;
		}
	}

	dev->member = dev->host_mask;

	for (i = 0; i < dev->mib_port_cnt; i++) {
		if (i == dev->cpu_port)
			continue;
		p = &dev->ports[i];

		/* Initialize to non-zero so that ksz_cfg_port_member() will
		 * be called.
		 */
		p->vid_member = (1 << i);
		p->member = dev->port_mask;
		ksz9477_port_stp_state_set(ds, i, BR_STATE_DISABLED);
		p->on = 1;
		if (i < dev->phy_port_cnt)
			p->phy = 1;
		if (dev->chip_id == 0x00947700 && i == 6) {
			p->sgmii = 1;

			/* SGMII PHY detection code is not implemented yet. */
			p->phy = 0;
		}
	}
}