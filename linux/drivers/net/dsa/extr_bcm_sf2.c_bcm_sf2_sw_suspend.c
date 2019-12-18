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
struct dsa_switch {unsigned int num_ports; } ;
struct bcm_sf2_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sf2_intr_disable (struct bcm_sf2_priv*) ; 
 int /*<<< orphan*/  bcm_sf2_port_disable (struct dsa_switch*,unsigned int) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,unsigned int) ; 
 scalar_t__ dsa_is_user_port (struct dsa_switch*,unsigned int) ; 

__attribute__((used)) static int bcm_sf2_sw_suspend(struct dsa_switch *ds)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	unsigned int port;

	bcm_sf2_intr_disable(priv);

	/* Disable all ports physically present including the IMP
	 * port, the other ones have already been disabled during
	 * bcm_sf2_sw_setup
	 */
	for (port = 0; port < ds->num_ports; port++) {
		if (dsa_is_user_port(ds, port) || dsa_is_cpu_port(ds, port))
			bcm_sf2_port_disable(ds, port);
	}

	return 0;
}