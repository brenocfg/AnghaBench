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
struct tja11xx_priv {char* hwmon_name; int /*<<< orphan*/  hwmon_dev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct phy_device {TYPE_1__ mdio; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_hwmon_device_register_with_info (struct device*,char*,struct phy_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* devm_kstrdup (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tja11xx_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ hwmon_is_bad_char (char) ; 
 int /*<<< orphan*/  tja11xx_hwmon_chip_info ; 

__attribute__((used)) static int tja11xx_probe(struct phy_device *phydev)
{
	struct device *dev = &phydev->mdio.dev;
	struct tja11xx_priv *priv;
	int i;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->hwmon_name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	if (!priv->hwmon_name)
		return -ENOMEM;

	for (i = 0; priv->hwmon_name[i]; i++)
		if (hwmon_is_bad_char(priv->hwmon_name[i]))
			priv->hwmon_name[i] = '_';

	priv->hwmon_dev =
		devm_hwmon_device_register_with_info(dev, priv->hwmon_name,
						     phydev,
						     &tja11xx_hwmon_chip_info,
						     NULL);

	return PTR_ERR_OR_ZERO(priv->hwmon_dev);
}