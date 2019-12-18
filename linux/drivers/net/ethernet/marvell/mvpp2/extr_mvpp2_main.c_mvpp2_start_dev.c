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
struct phylink_link_state {int /*<<< orphan*/  interface; } ;
struct mvpp2_port {int nqvecs; int /*<<< orphan*/  dev; int /*<<< orphan*/  phy_interface; int /*<<< orphan*/  phylink_config; scalar_t__ phylink; TYPE_2__* priv; TYPE_1__* qvecs; } ;
struct TYPE_4__ {scalar_t__ hw_version; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLO_AN_INBAND ; 
 scalar_t__ MVPP22 ; 
 int /*<<< orphan*/  mvpp22_mode_reconfigure (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_interrupts_enable (struct mvpp2_port*) ; 
 int /*<<< orphan*/  mvpp2_mac_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct phylink_link_state*) ; 
 int /*<<< orphan*/  mvpp2_mac_link_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_txp_max_tx_size_set (struct mvpp2_port*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_start (scalar_t__) ; 

__attribute__((used)) static void mvpp2_start_dev(struct mvpp2_port *port)
{
	int i;

	mvpp2_txp_max_tx_size_set(port);

	for (i = 0; i < port->nqvecs; i++)
		napi_enable(&port->qvecs[i].napi);

	/* Enable interrupts on all threads */
	mvpp2_interrupts_enable(port);

	if (port->priv->hw_version == MVPP22)
		mvpp22_mode_reconfigure(port);

	if (port->phylink) {
		phylink_start(port->phylink);
	} else {
		/* Phylink isn't used as of now for ACPI, so the MAC has to be
		 * configured manually when the interface is started. This will
		 * be removed as soon as the phylink ACPI support lands in.
		 */
		struct phylink_link_state state = {
			.interface = port->phy_interface,
		};
		mvpp2_mac_config(&port->phylink_config, MLO_AN_INBAND, &state);
		mvpp2_mac_link_up(&port->phylink_config, MLO_AN_INBAND,
				  port->phy_interface, NULL);
	}

	netif_tx_start_all_queues(port->dev);
}