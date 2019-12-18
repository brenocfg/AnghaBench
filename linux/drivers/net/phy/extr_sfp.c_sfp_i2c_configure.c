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
struct sfp {struct mii_bus* i2c_mii; int /*<<< orphan*/  dev; int /*<<< orphan*/  write; int /*<<< orphan*/  read; struct i2c_adapter* i2c; } ;
struct mii_bus {char* name; int /*<<< orphan*/  phy_mask; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 scalar_t__ IS_ERR (struct mii_bus*) ; 
 int PTR_ERR (struct mii_bus*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 struct mii_bus* mdio_i2c_alloc (int /*<<< orphan*/ ,struct i2c_adapter*) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int mdiobus_register (struct mii_bus*) ; 
 int /*<<< orphan*/  sfp_i2c_read ; 
 int /*<<< orphan*/  sfp_i2c_write ; 

__attribute__((used)) static int sfp_i2c_configure(struct sfp *sfp, struct i2c_adapter *i2c)
{
	struct mii_bus *i2c_mii;
	int ret;

	if (!i2c_check_functionality(i2c, I2C_FUNC_I2C))
		return -EINVAL;

	sfp->i2c = i2c;
	sfp->read = sfp_i2c_read;
	sfp->write = sfp_i2c_write;

	i2c_mii = mdio_i2c_alloc(sfp->dev, i2c);
	if (IS_ERR(i2c_mii))
		return PTR_ERR(i2c_mii);

	i2c_mii->name = "SFP I2C Bus";
	i2c_mii->phy_mask = ~0;

	ret = mdiobus_register(i2c_mii);
	if (ret < 0) {
		mdiobus_free(i2c_mii);
		return ret;
	}

	sfp->i2c_mii = i2c_mii;

	return 0;
}