#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_6__ {int nr; TYPE_1__ dev; int /*<<< orphan*/ * quirks; int /*<<< orphan*/  timeout; } ;
struct mlxcpld_i2c_priv {int smbus_block; int /*<<< orphan*/  lock; TYPE_2__ adap; int /*<<< orphan*/  base_addr; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLXCPLD_I2C_DATA_SZ_BIT ; 
 int MLXCPLD_I2C_DATA_SZ_MASK ; 
 int MLXCPLD_I2C_SMBUS_BLK_BIT ; 
 int /*<<< orphan*/  MLXCPLD_I2C_XFER_TO ; 
 int /*<<< orphan*/  MLXCPLD_LPCI2C_CPBLTY_REG ; 
 int /*<<< orphan*/  MLXPLAT_CPLD_LPC_I2C_BASE_ADDR ; 
 struct mlxcpld_i2c_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int i2c_add_numbered_adapter (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_set_adapdata (TYPE_2__*,struct mlxcpld_i2c_priv*) ; 
 TYPE_2__ mlxcpld_i2c_adapter ; 
 int /*<<< orphan*/  mlxcpld_i2c_quirks_ext ; 
 int /*<<< orphan*/  mlxcpld_i2c_read_comm (struct mlxcpld_i2c_priv*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mlxcpld_i2c_priv*) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxcpld_i2c_probe(struct platform_device *pdev)
{
	struct mlxcpld_i2c_priv *priv;
	int err;
	u8 val;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	mutex_init(&priv->lock);
	platform_set_drvdata(pdev, priv);

	priv->dev = &pdev->dev;
	priv->base_addr = MLXPLAT_CPLD_LPC_I2C_BASE_ADDR;

	/* Register with i2c layer */
	mlxcpld_i2c_adapter.timeout = usecs_to_jiffies(MLXCPLD_I2C_XFER_TO);
	/* Read capability register */
	mlxcpld_i2c_read_comm(priv, MLXCPLD_LPCI2C_CPBLTY_REG, &val, 1);
	/* Check support for extended transaction length */
	if ((val & MLXCPLD_I2C_DATA_SZ_MASK) == MLXCPLD_I2C_DATA_SZ_BIT)
		mlxcpld_i2c_adapter.quirks = &mlxcpld_i2c_quirks_ext;
	/* Check support for smbus block transaction */
	if (val & MLXCPLD_I2C_SMBUS_BLK_BIT)
		priv->smbus_block = true;
	if (pdev->id >= -1)
		mlxcpld_i2c_adapter.nr = pdev->id;
	priv->adap = mlxcpld_i2c_adapter;
	priv->adap.dev.parent = &pdev->dev;
	i2c_set_adapdata(&priv->adap, priv);

	err = i2c_add_numbered_adapter(&priv->adap);
	if (err)
		mutex_destroy(&priv->lock);

	return err;
}