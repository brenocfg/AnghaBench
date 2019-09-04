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
struct ksz_device {int port_cnt; int cpu_ports; int cpu_port; } ;
struct dsa_switch {int num_ports; struct ksz_device* priv; } ;

/* Variables and functions */
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,int) ; 
 int /*<<< orphan*/  port_setup (struct ksz_device*,int,int) ; 

__attribute__((used)) static void ksz_config_cpu_port(struct dsa_switch *ds)
{
	struct ksz_device *dev = ds->priv;
	int i;

	ds->num_ports = dev->port_cnt;

	for (i = 0; i < ds->num_ports; i++) {
		if (dsa_is_cpu_port(ds, i) && (dev->cpu_ports & (1 << i))) {
			dev->cpu_port = i;

			/* enable cpu port */
			port_setup(dev, i, true);
		}
	}
}