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
struct ksz_device {int dummy; } ;
struct dsa_switch {struct ksz_device* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_VLAN_LOOKUP_VID_0 ; 
 int /*<<< orphan*/  REG_PORT_LUE_CTRL ; 
 int /*<<< orphan*/  REG_SW_LUE_CTRL_0 ; 
 int /*<<< orphan*/  SW_VLAN_ENABLE ; 
 int /*<<< orphan*/  ksz_cfg (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ksz_port_cfg (struct ksz_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz9477_port_vlan_filtering(struct dsa_switch *ds, int port,
				       bool flag)
{
	struct ksz_device *dev = ds->priv;

	if (flag) {
		ksz_port_cfg(dev, port, REG_PORT_LUE_CTRL,
			     PORT_VLAN_LOOKUP_VID_0, true);
		ksz_cfg(dev, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, true);
	} else {
		ksz_cfg(dev, REG_SW_LUE_CTRL_0, SW_VLAN_ENABLE, false);
		ksz_port_cfg(dev, port, REG_PORT_LUE_CTRL,
			     PORT_VLAN_LOOKUP_VID_0, false);
	}

	return 0;
}