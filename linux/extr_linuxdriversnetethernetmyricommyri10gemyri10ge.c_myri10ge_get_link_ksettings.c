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
struct net_device {int dummy; } ;
struct myri10ge_priv {char* product_code_string; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  FIBRE ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  ethtool_link_ksettings_add_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 struct myri10ge_priv* netdev_priv (struct net_device*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int
myri10ge_get_link_ksettings(struct net_device *netdev,
			    struct ethtool_link_ksettings *cmd)
{
	struct myri10ge_priv *mgp = netdev_priv(netdev);
	char *ptr;
	int i;

	cmd->base.autoneg = AUTONEG_DISABLE;
	cmd->base.speed = SPEED_10000;
	cmd->base.duplex = DUPLEX_FULL;

	/*
	 * parse the product code to deterimine the interface type
	 * (CX4, XFP, Quad Ribbon Fiber) by looking at the character
	 * after the 3rd dash in the driver's cached copy of the
	 * EEPROM's product code string.
	 */
	ptr = mgp->product_code_string;
	if (ptr == NULL) {
		netdev_err(netdev, "Missing product code\n");
		return 0;
	}
	for (i = 0; i < 3; i++, ptr++) {
		ptr = strchr(ptr, '-');
		if (ptr == NULL) {
			netdev_err(netdev, "Invalid product code %s\n",
				   mgp->product_code_string);
			return 0;
		}
	}
	if (*ptr == '2')
		ptr++;
	if (*ptr == 'R' || *ptr == 'Q' || *ptr == 'S') {
		/* We've found either an XFP, quad ribbon fiber, or SFP+ */
		cmd->base.port = PORT_FIBRE;
		ethtool_link_ksettings_add_link_mode(cmd, supported, FIBRE);
		ethtool_link_ksettings_add_link_mode(cmd, advertising, FIBRE);
	} else {
		cmd->base.port = PORT_OTHER;
	}

	return 0;
}