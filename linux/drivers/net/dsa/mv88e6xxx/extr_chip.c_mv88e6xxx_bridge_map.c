#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct mv88e6xxx_chip {TYPE_3__* ds; } ;
struct dsa_switch {int num_ports; TYPE_4__* ports; } ;
struct TYPE_8__ {struct net_device* bridge_dev; } ;
struct TYPE_7__ {TYPE_2__* dst; TYPE_1__* ports; } ;
struct TYPE_6__ {struct dsa_switch** ds; } ;
struct TYPE_5__ {struct net_device* bridge_dev; } ;

/* Variables and functions */
 int DSA_MAX_SWITCHES ; 
 int /*<<< orphan*/  mv88e6xxx_has_pvt (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_num_ports (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_port_vlan_map (struct mv88e6xxx_chip*,int) ; 
 int mv88e6xxx_pvt_map (struct mv88e6xxx_chip*,int,int) ; 

__attribute__((used)) static int mv88e6xxx_bridge_map(struct mv88e6xxx_chip *chip,
				struct net_device *br)
{
	struct dsa_switch *ds;
	int port;
	int dev;
	int err;

	/* Remap the Port VLAN of each local bridge group member */
	for (port = 0; port < mv88e6xxx_num_ports(chip); ++port) {
		if (chip->ds->ports[port].bridge_dev == br) {
			err = mv88e6xxx_port_vlan_map(chip, port);
			if (err)
				return err;
		}
	}

	if (!mv88e6xxx_has_pvt(chip))
		return 0;

	/* Remap the Port VLAN of each cross-chip bridge group member */
	for (dev = 0; dev < DSA_MAX_SWITCHES; ++dev) {
		ds = chip->ds->dst->ds[dev];
		if (!ds)
			break;

		for (port = 0; port < ds->num_ports; ++port) {
			if (ds->ports[port].bridge_dev == br) {
				err = mv88e6xxx_pvt_map(chip, dev, port);
				if (err)
					return err;
			}
		}
	}

	return 0;
}