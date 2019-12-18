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
typedef  int u8 ;
struct net_device {int priv_flags; } ;
struct ksz_switch {int member; } ;
struct ksz_hw {int promiscuous; int features; struct ksz_switch* ksz_switch; } ;
struct TYPE_2__ {int first_port; } ;
struct dev_priv {int promiscuous; TYPE_1__ port; } ;

/* Variables and functions */
 int IFF_BRIDGE_PORT ; 
 int /*<<< orphan*/  STP_STATE_DISABLED ; 
 int STP_SUPPORT ; 
 int /*<<< orphan*/  bridge_change (struct ksz_hw*) ; 
 int /*<<< orphan*/  hw_set_promiscuous (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  port_set_stp_state (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_set_promiscuous(struct net_device *dev, struct dev_priv *priv,
	struct ksz_hw *hw, int promiscuous)
{
	if (promiscuous != priv->promiscuous) {
		u8 prev_state = hw->promiscuous;

		if (promiscuous)
			++hw->promiscuous;
		else
			--hw->promiscuous;
		priv->promiscuous = promiscuous;

		/* Turn on/off promiscuous mode. */
		if (hw->promiscuous <= 1 && prev_state <= 1)
			hw_set_promiscuous(hw, hw->promiscuous);

		/*
		 * Port is not in promiscuous mode, meaning it is released
		 * from the bridge.
		 */
		if ((hw->features & STP_SUPPORT) && !promiscuous &&
		    (dev->priv_flags & IFF_BRIDGE_PORT)) {
			struct ksz_switch *sw = hw->ksz_switch;
			int port = priv->port.first_port;

			port_set_stp_state(hw, port, STP_STATE_DISABLED);
			port = 1 << port;
			if (sw->member & port) {
				sw->member &= ~port;
				bridge_change(hw);
			}
		}
	}
}