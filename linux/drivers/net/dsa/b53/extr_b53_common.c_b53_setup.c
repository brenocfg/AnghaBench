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
struct dsa_switch {int vlan_filtering_is_global; int /*<<< orphan*/  dev; struct b53_device* priv; } ;
struct b53_device {unsigned int num_ports; } ;

/* Variables and functions */
 int b53_apply_config (struct b53_device*) ; 
 int /*<<< orphan*/  b53_disable_port (struct dsa_switch*,unsigned int) ; 
 int /*<<< orphan*/  b53_enable_cpu_port (struct b53_device*,unsigned int) ; 
 int /*<<< orphan*/  b53_reset_mib (struct b53_device*) ; 
 int b53_reset_switch (struct b53_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,unsigned int) ; 

__attribute__((used)) static int b53_setup(struct dsa_switch *ds)
{
	struct b53_device *dev = ds->priv;
	unsigned int port;
	int ret;

	ret = b53_reset_switch(dev);
	if (ret) {
		dev_err(ds->dev, "failed to reset switch\n");
		return ret;
	}

	b53_reset_mib(dev);

	ret = b53_apply_config(dev);
	if (ret)
		dev_err(ds->dev, "failed to apply configuration\n");

	/* Configure IMP/CPU port, disable all other ports. Enabled
	 * ports will be configured with .port_enable
	 */
	for (port = 0; port < dev->num_ports; port++) {
		if (dsa_is_cpu_port(ds, port))
			b53_enable_cpu_port(dev, port);
		else
			b53_disable_port(ds, port);
	}

	/* Let DSA handle the case were multiple bridges span the same switch
	 * device and different VLAN awareness settings are requested, which
	 * would be breaking filtering semantics for any of the other bridge
	 * devices. (not hardware supported)
	 */
	ds->vlan_filtering_is_global = true;

	return ret;
}