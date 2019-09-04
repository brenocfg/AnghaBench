#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct phylink_link_state {int link; int /*<<< orphan*/  duplex; } ;
struct dsa_switch {TYPE_1__* ports; } ;
struct bcm_sf2_priv {int moca_port; TYPE_2__* port_sts; } ;
struct TYPE_4__ {int link; } ;
struct TYPE_3__ {int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_sw_fixed_state(struct dsa_switch *ds, int port,
				   struct phylink_link_state *status)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);

	status->link = false;

	/* MoCA port is special as we do not get link status from CORE_LNKSTS,
	 * which means that we need to force the link at the port override
	 * level to get the data to flow. We do use what the interrupt handler
	 * did determine before.
	 *
	 * For the other ports, we just force the link status, since this is
	 * a fixed PHY device.
	 */
	if (port == priv->moca_port) {
		status->link = priv->port_sts[port].link;
		/* For MoCA interfaces, also force a link down notification
		 * since some version of the user-space daemon (mocad) use
		 * cmd->autoneg to force the link, which messes up the PHY
		 * state machine and make it go in PHY_FORCING state instead.
		 */
		if (!status->link)
			netif_carrier_off(ds->ports[port].slave);
		status->duplex = DUPLEX_FULL;
	} else {
		status->link = true;
	}
}