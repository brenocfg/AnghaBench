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
typedef  int u32 ;
struct realtek_smi {int num_ports; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int EINVAL ; 
 int RTL8366RB_PORT_VLAN_CTRL_MASK ; 
 int /*<<< orphan*/  RTL8366RB_PORT_VLAN_CTRL_REG (int) ; 
 int RTL8366RB_PORT_VLAN_CTRL_SHIFT (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int rtl8366rb_get_mc_index(struct realtek_smi *smi, int port, int *val)
{
	u32 data;
	int ret;

	if (port >= smi->num_ports)
		return -EINVAL;

	ret = regmap_read(smi->map, RTL8366RB_PORT_VLAN_CTRL_REG(port),
			  &data);
	if (ret)
		return ret;

	*val = (data >> RTL8366RB_PORT_VLAN_CTRL_SHIFT(port)) &
		RTL8366RB_PORT_VLAN_CTRL_MASK;

	return 0;
}