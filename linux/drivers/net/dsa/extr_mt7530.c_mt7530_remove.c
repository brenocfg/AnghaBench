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
struct mt7530_priv {int /*<<< orphan*/  reg_mutex; int /*<<< orphan*/  ds; int /*<<< orphan*/  dev; int /*<<< orphan*/  io_pwr; int /*<<< orphan*/  core_pwr; } ;
struct mdio_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct mt7530_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_unregister_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt7530_remove(struct mdio_device *mdiodev)
{
	struct mt7530_priv *priv = dev_get_drvdata(&mdiodev->dev);
	int ret = 0;

	ret = regulator_disable(priv->core_pwr);
	if (ret < 0)
		dev_err(priv->dev,
			"Failed to disable core power: %d\n", ret);

	ret = regulator_disable(priv->io_pwr);
	if (ret < 0)
		dev_err(priv->dev, "Failed to disable io pwr: %d\n",
			ret);

	dsa_unregister_switch(priv->ds);
	mutex_destroy(&priv->reg_mutex);
}