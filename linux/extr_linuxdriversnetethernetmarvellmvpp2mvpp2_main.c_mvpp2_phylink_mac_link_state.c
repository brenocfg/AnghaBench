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
typedef  int /*<<< orphan*/  u32 ;
struct phylink_link_state {int dummy; } ;
struct net_device {int dummy; } ;
struct mvpp2_port {scalar_t__ gop_id; scalar_t__ base; TYPE_1__* priv; } ;
struct TYPE_2__ {scalar_t__ hw_version; } ;

/* Variables and functions */
 scalar_t__ MVPP22 ; 
 int /*<<< orphan*/  MVPP22_XLG_CTRL3_MACMODESELECT_10G ; 
 int /*<<< orphan*/  MVPP22_XLG_CTRL3_MACMODESELECT_MASK ; 
 scalar_t__ MVPP22_XLG_CTRL3_REG ; 
 int /*<<< orphan*/  mvpp22_xlg_link_state (struct mvpp2_port*,struct phylink_link_state*) ; 
 int /*<<< orphan*/  mvpp2_gmac_link_state (struct mvpp2_port*,struct phylink_link_state*) ; 
 struct mvpp2_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static int mvpp2_phylink_mac_link_state(struct net_device *dev,
					struct phylink_link_state *state)
{
	struct mvpp2_port *port = netdev_priv(dev);

	if (port->priv->hw_version == MVPP22 && port->gop_id == 0) {
		u32 mode = readl(port->base + MVPP22_XLG_CTRL3_REG);
		mode &= MVPP22_XLG_CTRL3_MACMODESELECT_MASK;

		if (mode == MVPP22_XLG_CTRL3_MACMODESELECT_10G) {
			mvpp22_xlg_link_state(port, state);
			return 1;
		}
	}

	mvpp2_gmac_link_state(port, state);
	return 1;
}