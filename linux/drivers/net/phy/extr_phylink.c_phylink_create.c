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
struct phylink_mac_ops {int dummy; } ;
struct phylink_config {scalar_t__ type; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int an_enabled; int /*<<< orphan*/  advertising; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  pause; scalar_t__ interface; } ;
struct TYPE_3__ {scalar_t__ interface; } ;
struct phylink {scalar_t__ link_an_mode; TYPE_2__ link_config; int /*<<< orphan*/  supported; int /*<<< orphan*/  link_poll; int /*<<< orphan*/  phylink_disable_state; struct phylink_mac_ops const* ops; int /*<<< orphan*/  link_port; scalar_t__ link_interface; TYPE_1__ phy_state; int /*<<< orphan*/  dev; int /*<<< orphan*/  netdev; struct phylink_config* config; int /*<<< orphan*/  resolve; int /*<<< orphan*/  state_mutex; } ;
struct fwnode_handle {int dummy; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct phylink* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MLO_AN_FIXED ; 
 int /*<<< orphan*/  MLO_PAUSE_AN ; 
 scalar_t__ PHYLINK_DEV ; 
 int /*<<< orphan*/  PHYLINK_DISABLE_STOPPED ; 
 scalar_t__ PHYLINK_NETDEV ; 
 scalar_t__ PHY_INTERFACE_MODE_MOCA ; 
 int /*<<< orphan*/  PORT_BNC ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct phylink*) ; 
 struct phylink* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phylink_fixed_poll ; 
 int phylink_parse_fixedlink (struct phylink*,struct fwnode_handle*) ; 
 int phylink_parse_mode (struct phylink*,struct fwnode_handle*) ; 
 int phylink_register_sfp (struct phylink*,struct fwnode_handle*) ; 
 int /*<<< orphan*/  phylink_resolve ; 
 int /*<<< orphan*/  phylink_validate (struct phylink*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_net_dev (int /*<<< orphan*/ ) ; 

struct phylink *phylink_create(struct phylink_config *config,
			       struct fwnode_handle *fwnode,
			       phy_interface_t iface,
			       const struct phylink_mac_ops *ops)
{
	struct phylink *pl;
	int ret;

	pl = kzalloc(sizeof(*pl), GFP_KERNEL);
	if (!pl)
		return ERR_PTR(-ENOMEM);

	mutex_init(&pl->state_mutex);
	INIT_WORK(&pl->resolve, phylink_resolve);

	pl->config = config;
	if (config->type == PHYLINK_NETDEV) {
		pl->netdev = to_net_dev(config->dev);
	} else if (config->type == PHYLINK_DEV) {
		pl->dev = config->dev;
	} else {
		kfree(pl);
		return ERR_PTR(-EINVAL);
	}

	pl->phy_state.interface = iface;
	pl->link_interface = iface;
	if (iface == PHY_INTERFACE_MODE_MOCA)
		pl->link_port = PORT_BNC;
	else
		pl->link_port = PORT_MII;
	pl->link_config.interface = iface;
	pl->link_config.pause = MLO_PAUSE_AN;
	pl->link_config.speed = SPEED_UNKNOWN;
	pl->link_config.duplex = DUPLEX_UNKNOWN;
	pl->link_config.an_enabled = true;
	pl->ops = ops;
	__set_bit(PHYLINK_DISABLE_STOPPED, &pl->phylink_disable_state);
	timer_setup(&pl->link_poll, phylink_fixed_poll, 0);

	bitmap_fill(pl->supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	linkmode_copy(pl->link_config.advertising, pl->supported);
	phylink_validate(pl, pl->supported, &pl->link_config);

	ret = phylink_parse_mode(pl, fwnode);
	if (ret < 0) {
		kfree(pl);
		return ERR_PTR(ret);
	}

	if (pl->link_an_mode == MLO_AN_FIXED) {
		ret = phylink_parse_fixedlink(pl, fwnode);
		if (ret < 0) {
			kfree(pl);
			return ERR_PTR(ret);
		}
	}

	ret = phylink_register_sfp(pl, fwnode);
	if (ret < 0) {
		kfree(pl);
		return ERR_PTR(ret);
	}

	return pl;
}