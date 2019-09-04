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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct phylink_link_state {scalar_t__ interface; int link; int an_enabled; int an_complete; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct mv88e6xxx_chip {TYPE_1__* ports; } ;
struct TYPE_2__ {scalar_t__ cmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int MV88E6185_PORT_MAC_CTL_AN_DONE ; 
 int MV88E6185_PORT_MAC_CTL_SYNC_OK ; 
 scalar_t__ MV88E6185_PORT_STS_CMODE_SERDES ; 
 int /*<<< orphan*/  MV88E6XXX_PORT_MAC_CTL ; 
 scalar_t__ PHY_INTERFACE_MODE_1000BASEX ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int mv88e6352_port_link_state (struct mv88e6xxx_chip*,int,struct phylink_link_state*) ; 
 int mv88e6xxx_port_read (struct mv88e6xxx_chip*,int,int /*<<< orphan*/ ,int*) ; 

int mv88e6185_port_link_state(struct mv88e6xxx_chip *chip, int port,
			      struct phylink_link_state *state)
{
	if (state->interface == PHY_INTERFACE_MODE_1000BASEX) {
		u8 cmode = chip->ports[port].cmode;

		/* When a port is in "Cross-chip serdes" mode, it uses
		 * 1000Base-X full duplex mode, but there is no automatic
		 * link detection. Use the sync OK status for link (as it
		 * would do for 1000Base-X mode.)
		 */
		if (cmode == MV88E6185_PORT_STS_CMODE_SERDES) {
			u16 mac;
			int err;

			err = mv88e6xxx_port_read(chip, port,
						  MV88E6XXX_PORT_MAC_CTL, &mac);
			if (err)
				return err;

			state->link = !!(mac & MV88E6185_PORT_MAC_CTL_SYNC_OK);
			state->an_enabled = 1;
			state->an_complete =
				!!(mac & MV88E6185_PORT_MAC_CTL_AN_DONE);
			state->duplex =
				state->link ? DUPLEX_FULL : DUPLEX_UNKNOWN;
			state->speed =
				state->link ? SPEED_1000 : SPEED_UNKNOWN;

			return 0;
		}
	}

	return mv88e6352_port_link_state(chip, port, state);
}