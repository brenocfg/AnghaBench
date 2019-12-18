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
struct dsa_switch {int dummy; } ;
struct TYPE_2__ {unsigned int num_ports; } ;
struct bcm_sf2_priv {TYPE_1__ hw_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  b53_configure_vlan (struct dsa_switch*) ; 
 int /*<<< orphan*/  bcm_sf2_enable_acb (struct dsa_switch*) ; 
 int /*<<< orphan*/  bcm_sf2_imp_setup (struct dsa_switch*,unsigned int) ; 
 int /*<<< orphan*/  bcm_sf2_port_disable (struct dsa_switch*,unsigned int) ; 
 int /*<<< orphan*/  bcm_sf2_port_setup (struct dsa_switch*,unsigned int,int /*<<< orphan*/ *) ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 scalar_t__ dsa_is_cpu_port (struct dsa_switch*,unsigned int) ; 
 scalar_t__ dsa_is_user_port (struct dsa_switch*,unsigned int) ; 

__attribute__((used)) static int bcm_sf2_sw_setup(struct dsa_switch *ds)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	unsigned int port;

	/* Enable all valid ports and disable those unused */
	for (port = 0; port < priv->hw_params.num_ports; port++) {
		/* IMP port receives special treatment */
		if (dsa_is_user_port(ds, port))
			bcm_sf2_port_setup(ds, port, NULL);
		else if (dsa_is_cpu_port(ds, port))
			bcm_sf2_imp_setup(ds, port);
		else
			bcm_sf2_port_disable(ds, port);
	}

	b53_configure_vlan(ds);
	bcm_sf2_enable_acb(ds);

	return 0;
}