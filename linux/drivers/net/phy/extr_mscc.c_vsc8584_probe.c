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
typedef  int /*<<< orphan*/  u32 ;
struct vsc8531_private {int nleds; int /*<<< orphan*/  stats; int /*<<< orphan*/  nstats; int /*<<< orphan*/  hw_stats; int /*<<< orphan*/  supp_led_modes; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {int phy_id; TYPE_1__ mdio; struct vsc8531_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MSCC_DEV_REV_MASK ; 
 int /*<<< orphan*/  VSC8531_DUPLEX_COLLISION ; 
 int /*<<< orphan*/  VSC8531_LINK_1000_ACTIVITY ; 
 int /*<<< orphan*/  VSC8531_LINK_100_ACTIVITY ; 
 int /*<<< orphan*/  VSC8531_LINK_ACTIVITY ; 
 int VSC8584_REVB ; 
 int /*<<< orphan*/  VSC8584_SUPP_LED_MODES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct vsc8531_private* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsc8584_hw_stats ; 
 int vsc85xx_dt_led_modes_get (struct phy_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vsc8584_probe(struct phy_device *phydev)
{
	struct vsc8531_private *vsc8531;
	u32 default_mode[4] = {VSC8531_LINK_1000_ACTIVITY,
	   VSC8531_LINK_100_ACTIVITY, VSC8531_LINK_ACTIVITY,
	   VSC8531_DUPLEX_COLLISION};

	if ((phydev->phy_id & MSCC_DEV_REV_MASK) != VSC8584_REVB) {
		dev_err(&phydev->mdio.dev, "Only VSC8584 revB is supported.\n");
		return -ENOTSUPP;
	}

	vsc8531 = devm_kzalloc(&phydev->mdio.dev, sizeof(*vsc8531), GFP_KERNEL);
	if (!vsc8531)
		return -ENOMEM;

	phydev->priv = vsc8531;

	vsc8531->nleds = 4;
	vsc8531->supp_led_modes = VSC8584_SUPP_LED_MODES;
	vsc8531->hw_stats = vsc8584_hw_stats;
	vsc8531->nstats = ARRAY_SIZE(vsc8584_hw_stats);
	vsc8531->stats = devm_kcalloc(&phydev->mdio.dev, vsc8531->nstats,
				      sizeof(u64), GFP_KERNEL);
	if (!vsc8531->stats)
		return -ENOMEM;

	return vsc85xx_dt_led_modes_get(phydev, default_mode);
}