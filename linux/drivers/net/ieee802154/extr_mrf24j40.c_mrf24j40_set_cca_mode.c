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
struct mrf24j40 {int /*<<< orphan*/  regmap_short; } ;
struct ieee802154_hw {struct mrf24j40* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBREG2_CCA_MODE_MASK ; 
 int BBREG2_CCA_MODE_SHIFT ; 
 int EINVAL ; 
#define  NL802154_CCA_CARRIER 131 
#define  NL802154_CCA_ENERGY 130 
#define  NL802154_CCA_ENERGY_CARRIER 129 
#define  NL802154_CCA_OPT_ENERGY_CARRIER_AND 128 
 int /*<<< orphan*/  REG_BBREG2 ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mrf24j40_set_cca_mode(struct ieee802154_hw *hw,
				 const struct wpan_phy_cca *cca)
{
	struct mrf24j40 *devrec = hw->priv;
	u8 val;

	/* mapping 802.15.4 to driver spec */
	switch (cca->mode) {
	case NL802154_CCA_ENERGY:
		val = 2;
		break;
	case NL802154_CCA_CARRIER:
		val = 1;
		break;
	case NL802154_CCA_ENERGY_CARRIER:
		switch (cca->opt) {
		case NL802154_CCA_OPT_ENERGY_CARRIER_AND:
			val = 3;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(devrec->regmap_short, REG_BBREG2,
				  BBREG2_CCA_MODE_MASK,
				  val << BBREG2_CCA_MODE_SHIFT);
}