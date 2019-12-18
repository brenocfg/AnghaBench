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
struct mt7530_priv {struct mii_bus* bus; } ;
struct mii_bus {int (* write ) (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_MMD_CTRL ; 
 int MII_MMD_CTRL_NOINCR ; 
 int /*<<< orphan*/  MII_MMD_DATA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub3 (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub4 (struct mii_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
core_write_mmd_indirect(struct mt7530_priv *priv, int prtad,
			int devad, u32 data)
{
	struct mii_bus *bus = priv->bus;
	int ret;

	/* Write the desired MMD Devad */
	ret = bus->write(bus, 0, MII_MMD_CTRL, devad);
	if (ret < 0)
		goto err;

	/* Write the desired MMD register address */
	ret = bus->write(bus, 0, MII_MMD_DATA, prtad);
	if (ret < 0)
		goto err;

	/* Select the Function : DATA with no post increment */
	ret = bus->write(bus, 0, MII_MMD_CTRL, (devad | MII_MMD_CTRL_NOINCR));
	if (ret < 0)
		goto err;

	/* Write the data into MMD's selected register */
	ret = bus->write(bus, 0, MII_MMD_DATA, data);
err:
	if (ret < 0)
		dev_err(&bus->dev,
			"failed to write mmd register\n");
	return ret;
}