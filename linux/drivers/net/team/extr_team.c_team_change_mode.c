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
struct team_mode {int dummy; } ;
struct team {TYPE_1__* mode; int /*<<< orphan*/  port_list; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kind; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int __team_change_mode (struct team*,struct team_mode const*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ team_is_mode_set (struct team*) ; 
 struct team_mode* team_mode_get (char const*) ; 
 int /*<<< orphan*/  team_mode_put (struct team_mode const*) ; 

__attribute__((used)) static int team_change_mode(struct team *team, const char *kind)
{
	const struct team_mode *new_mode;
	struct net_device *dev = team->dev;
	int err;

	if (!list_empty(&team->port_list)) {
		netdev_err(dev, "No ports can be present during mode change\n");
		return -EBUSY;
	}

	if (team_is_mode_set(team) && strcmp(team->mode->kind, kind) == 0) {
		netdev_err(dev, "Unable to change to the same mode the team is in\n");
		return -EINVAL;
	}

	new_mode = team_mode_get(kind);
	if (!new_mode) {
		netdev_err(dev, "Mode \"%s\" not found\n", kind);
		return -EINVAL;
	}

	err = __team_change_mode(team, new_mode);
	if (err) {
		netdev_err(dev, "Failed to change to mode \"%s\"\n", kind);
		team_mode_put(new_mode);
		return err;
	}

	netdev_info(dev, "Mode changed to \"%s\"\n", kind);
	return 0;
}