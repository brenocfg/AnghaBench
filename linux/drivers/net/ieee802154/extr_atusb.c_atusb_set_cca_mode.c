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
typedef  int u8 ;
struct wpan_phy_cca {int mode; int /*<<< orphan*/  opt; } ;
struct ieee802154_hw {struct atusb* priv; } ;
struct atusb {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  NL802154_CCA_CARRIER 132 
#define  NL802154_CCA_ENERGY 131 
#define  NL802154_CCA_ENERGY_CARRIER 130 
#define  NL802154_CCA_OPT_ENERGY_CARRIER_AND 129 
#define  NL802154_CCA_OPT_ENERGY_CARRIER_OR 128 
 int /*<<< orphan*/  SR_CCA_MODE ; 
 int atusb_write_subreg (struct atusb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
atusb_set_cca_mode(struct ieee802154_hw *hw, const struct wpan_phy_cca *cca)
{
	struct atusb *atusb = hw->priv;
	u8 val;

	/* mapping 802.15.4 to driver spec */
	switch (cca->mode) {
	case NL802154_CCA_ENERGY:
		val = 1;
		break;
	case NL802154_CCA_CARRIER:
		val = 2;
		break;
	case NL802154_CCA_ENERGY_CARRIER:
		switch (cca->opt) {
		case NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			val = 3;
			break;
		case NL802154_CCA_OPT_ENERGY_CARRIER_OR:
			val = 0;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return atusb_write_subreg(atusb, SR_CCA_MODE, val);
}