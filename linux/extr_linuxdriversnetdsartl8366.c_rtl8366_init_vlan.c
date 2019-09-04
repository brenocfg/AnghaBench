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
struct realtek_smi {int num_ports; int cpu_port; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int rtl8366_enable_vlan (struct realtek_smi*,int) ; 
 int rtl8366_reset_vlan (struct realtek_smi*) ; 
 int rtl8366_set_pvid (struct realtek_smi*,int,int) ; 
 int rtl8366_set_vlan (struct realtek_smi*,int,int,int,int /*<<< orphan*/ ) ; 

int rtl8366_init_vlan(struct realtek_smi *smi)
{
	int port;
	int ret;

	ret = rtl8366_reset_vlan(smi);
	if (ret)
		return ret;

	/* Loop over the available ports, for each port, associate
	 * it with the VLAN (port+1)
	 */
	for (port = 0; port < smi->num_ports; port++) {
		u32 mask;

		if (port == smi->cpu_port)
			/* For the CPU port, make all ports members of this
			 * VLAN.
			 */
			mask = GENMASK(smi->num_ports - 1, 0);
		else
			/* For all other ports, enable itself plus the
			 * CPU port.
			 */
			mask = BIT(port) | BIT(smi->cpu_port);

		/* For each port, set the port as member of VLAN (port+1)
		 * and untagged, except for the CPU port: the CPU port (5) is
		 * member of VLAN 6 and so are ALL the other ports as well.
		 * Use filter 0 (no filter).
		 */
		dev_info(smi->dev, "VLAN%d port mask for port %d, %08x\n",
			 (port + 1), port, mask);
		ret = rtl8366_set_vlan(smi, (port + 1), mask, mask, 0);
		if (ret)
			return ret;

		dev_info(smi->dev, "VLAN%d port %d, PVID set to %d\n",
			 (port + 1), port, (port + 1));
		ret = rtl8366_set_pvid(smi, port, (port + 1));
		if (ret)
			return ret;
	}

	return rtl8366_enable_vlan(smi, true);
}