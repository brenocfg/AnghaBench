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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct histb_combphy_mode {int select; int shift; int /*<<< orphan*/  mask; int /*<<< orphan*/  reg; } ;
struct histb_combphy_priv {struct regmap* syscon; struct histb_combphy_mode mode; } ;

/* Variables and functions */
 int COMBPHY_MODE_PCIE ; 
 int COMBPHY_MODE_SATA ; 
 int COMBPHY_MODE_USB3 ; 
 int EINVAL ; 
#define  PHY_TYPE_PCIE 130 
#define  PHY_TYPE_SATA 129 
#define  PHY_TYPE_USB3 128 
 scalar_t__ is_mode_fixed (struct histb_combphy_mode*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int histb_combphy_set_mode(struct histb_combphy_priv *priv)
{
	struct histb_combphy_mode *mode = &priv->mode;
	struct regmap *syscon = priv->syscon;
	u32 hw_sel;

	if (is_mode_fixed(mode))
		return 0;

	switch (mode->select) {
	case PHY_TYPE_SATA:
		hw_sel = COMBPHY_MODE_SATA;
		break;
	case PHY_TYPE_PCIE:
		hw_sel = COMBPHY_MODE_PCIE;
		break;
	case PHY_TYPE_USB3:
		hw_sel = COMBPHY_MODE_USB3;
		break;
	default:
		return -EINVAL;
	}

	return regmap_update_bits(syscon, mode->reg, mode->mask,
				  hw_sel << mode->shift);
}