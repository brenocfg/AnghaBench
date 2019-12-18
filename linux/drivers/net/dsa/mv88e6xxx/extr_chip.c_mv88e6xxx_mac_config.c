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
struct phylink_link_state {int speed; int duplex; int link; int /*<<< orphan*/  interface; int /*<<< orphan*/  advertising; } ;
struct mv88e6xxx_chip {int dummy; } ;
struct dsa_switch {int /*<<< orphan*/  dev; struct mv88e6xxx_chip* priv; } ;

/* Variables and functions */
 int DUPLEX_UNFORCED ; 
 int EOPNOTSUPP ; 
 int LINK_FORCED_UP ; 
 int LINK_UNFORCED ; 
 unsigned int MLO_AN_FIXED ; 
 unsigned int MLO_AN_PHY ; 
 int /*<<< orphan*/  Pause ; 
 int SPEED_UNFORCED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ mv88e6xxx_phy_is_internal (struct dsa_switch*,int) ; 
 int mv88e6xxx_port_setup_mac (struct mv88e6xxx_chip*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6xxx_mac_config(struct dsa_switch *ds, int port,
				 unsigned int mode,
				 const struct phylink_link_state *state)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int speed, duplex, link, pause, err;

	if ((mode == MLO_AN_PHY) && mv88e6xxx_phy_is_internal(ds, port))
		return;

	if (mode == MLO_AN_FIXED) {
		link = LINK_FORCED_UP;
		speed = state->speed;
		duplex = state->duplex;
	} else if (!mv88e6xxx_phy_is_internal(ds, port)) {
		link = state->link;
		speed = state->speed;
		duplex = state->duplex;
	} else {
		speed = SPEED_UNFORCED;
		duplex = DUPLEX_UNFORCED;
		link = LINK_UNFORCED;
	}
	pause = !!phylink_test(state->advertising, Pause);

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_port_setup_mac(chip, port, link, speed, duplex, pause,
				       state->interface);
	mv88e6xxx_reg_unlock(chip);

	if (err && err != -EOPNOTSUPP)
		dev_err(ds->dev, "p%d: failed to configure MAC\n", port);
}