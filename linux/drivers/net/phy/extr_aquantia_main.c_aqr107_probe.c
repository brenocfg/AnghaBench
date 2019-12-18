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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct phy_device {int /*<<< orphan*/  priv; TYPE_1__ mdio; } ;
struct aqr107_priv {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int aqr_hwmon_probe (struct phy_device*) ; 
 int /*<<< orphan*/  devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqr107_probe(struct phy_device *phydev)
{
	phydev->priv = devm_kzalloc(&phydev->mdio.dev,
				    sizeof(struct aqr107_priv), GFP_KERNEL);
	if (!phydev->priv)
		return -ENOMEM;

	return aqr_hwmon_probe(phydev);
}