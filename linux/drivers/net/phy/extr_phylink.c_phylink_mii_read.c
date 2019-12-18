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
struct phylink_link_state {int dummy; } ;
struct phylink {int link_an_mode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  MLO_AN_FIXED 130 
#define  MLO_AN_INBAND 129 
#define  MLO_AN_PHY 128 
 int /*<<< orphan*/  phylink_get_fixed_state (struct phylink*,struct phylink_link_state*) ; 
 int phylink_get_mac_state (struct phylink*,struct phylink_link_state*) ; 
 int phylink_mii_emul_read (unsigned int,struct phylink_link_state*) ; 

__attribute__((used)) static int phylink_mii_read(struct phylink *pl, unsigned int phy_id,
			    unsigned int reg)
{
	struct phylink_link_state state;
	int val = 0xffff;

	switch (pl->link_an_mode) {
	case MLO_AN_FIXED:
		if (phy_id == 0) {
			phylink_get_fixed_state(pl, &state);
			val = phylink_mii_emul_read(reg, &state);
		}
		break;

	case MLO_AN_PHY:
		return -EOPNOTSUPP;

	case MLO_AN_INBAND:
		if (phy_id == 0) {
			val = phylink_get_mac_state(pl, &state);
			if (val < 0)
				return val;

			val = phylink_mii_emul_read(reg, &state);
		}
		break;
	}

	return val & 0xffff;
}