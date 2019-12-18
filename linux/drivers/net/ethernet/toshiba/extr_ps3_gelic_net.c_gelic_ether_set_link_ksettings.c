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
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct gelic_card {int dummy; } ;
struct TYPE_2__ {scalar_t__ autoneg; int speed; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ DUPLEX_FULL ; 
 int EINVAL ; 
 int /*<<< orphan*/  GELIC_LV1_ETHER_AUTO_NEG ; 
 int /*<<< orphan*/  GELIC_LV1_ETHER_FULL_DUPLEX ; 
 int /*<<< orphan*/  GELIC_LV1_ETHER_SPEED_10 ; 
 int /*<<< orphan*/  GELIC_LV1_ETHER_SPEED_100 ; 
 int /*<<< orphan*/  GELIC_LV1_ETHER_SPEED_1000 ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int gelic_card_set_link_mode (struct gelic_card*,int /*<<< orphan*/ ) ; 
 struct gelic_card* netdev_card (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int
gelic_ether_set_link_ksettings(struct net_device *netdev,
			       const struct ethtool_link_ksettings *cmd)
{
	struct gelic_card *card = netdev_card(netdev);
	u64 mode;
	int ret;

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		mode = GELIC_LV1_ETHER_AUTO_NEG;
	} else {
		switch (cmd->base.speed) {
		case SPEED_10:
			mode = GELIC_LV1_ETHER_SPEED_10;
			break;
		case SPEED_100:
			mode = GELIC_LV1_ETHER_SPEED_100;
			break;
		case SPEED_1000:
			mode = GELIC_LV1_ETHER_SPEED_1000;
			break;
		default:
			return -EINVAL;
		}
		if (cmd->base.duplex == DUPLEX_FULL) {
			mode |= GELIC_LV1_ETHER_FULL_DUPLEX;
		} else if (cmd->base.speed == SPEED_1000) {
			pr_info("1000 half duplex is not supported.\n");
			return -EINVAL;
		}
	}

	ret = gelic_card_set_link_mode(card, mode);

	if (ret)
		return ret;

	return 0;
}