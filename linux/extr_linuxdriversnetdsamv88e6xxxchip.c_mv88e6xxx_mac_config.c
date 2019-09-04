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
struct phylink_link_state {int speed; int duplex; int /*<<< orphan*/  interface; int /*<<< orphan*/  advertising; } ;
struct mv88e6xxx_chip {int /*<<< orphan*/  reg_lock; } ;
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
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mv88e6xxx_port_setup_mac (struct mv88e6xxx_chip*,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mv88e6xxx_mac_config(struct dsa_switch *ds, int port,
				 unsigned int mode,
				 const struct phylink_link_state *state)
{
	struct mv88e6xxx_chip *chip = ds->priv;
	int speed, duplex, link, pause, err;

	if (mode == MLO_AN_PHY)
		return;

	if (mode == MLO_AN_FIXED) {
		link = LINK_FORCED_UP;
		speed = state->speed;
		duplex = state->duplex;
	} else {
		speed = SPEED_UNFORCED;
		duplex = DUPLEX_UNFORCED;
		link = LINK_UNFORCED;
	}
	pause = !!phylink_test(state->advertising, Pause);

	mutex_lock(&chip->reg_lock);
	err = mv88e6xxx_port_setup_mac(chip, port, link, speed, duplex, pause,
				       state->interface);
	mutex_unlock(&chip->reg_lock);

	if (err && err != -EOPNOTSUPP)
		dev_err(ds->dev, "p%d: failed to configure MAC\n", port);
}