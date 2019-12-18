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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct stmfx {int /*<<< orphan*/ * vdd; int /*<<< orphan*/  map; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STMFX_REG_CHIP_ID ; 
 int /*<<< orphan*/  STMFX_REG_CHIP_ID_MASK ; 
 int /*<<< orphan*/  STMFX_REG_FW_VERSION_MSB ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_regulator_get_optional (int /*<<< orphan*/ *,char*) ; 
 struct stmfx* i2c_get_clientdata (struct i2c_client*) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int stmfx_chip_reset (struct stmfx*) ; 

__attribute__((used)) static int stmfx_chip_init(struct i2c_client *client)
{
	struct stmfx *stmfx = i2c_get_clientdata(client);
	u32 id;
	u8 version[2];
	int ret;

	stmfx->vdd = devm_regulator_get_optional(&client->dev, "vdd");
	ret = PTR_ERR_OR_ZERO(stmfx->vdd);
	if (ret == -ENODEV) {
		stmfx->vdd = NULL;
	} else if (ret == -EPROBE_DEFER) {
		return ret;
	} else if (ret) {
		dev_err(&client->dev, "Failed to get VDD regulator: %d\n", ret);
		return ret;
	}

	if (stmfx->vdd) {
		ret = regulator_enable(stmfx->vdd);
		if (ret) {
			dev_err(&client->dev, "VDD enable failed: %d\n", ret);
			return ret;
		}
	}

	ret = regmap_read(stmfx->map, STMFX_REG_CHIP_ID, &id);
	if (ret) {
		dev_err(&client->dev, "Error reading chip ID: %d\n", ret);
		goto err;
	}

	/*
	 * Check that ID is the complement of the I2C address:
	 * STMFX I2C address follows the 7-bit format (MSB), that's why
	 * client->addr is shifted.
	 *
	 * STMFX_I2C_ADDR|       STMFX         |        Linux
	 *   input pin   | I2C device address  | I2C device address
	 *---------------------------------------------------------
	 *       0       | b: 1000 010x h:0x84 |       0x42
	 *       1       | b: 1000 011x h:0x86 |       0x43
	 */
	if (FIELD_GET(STMFX_REG_CHIP_ID_MASK, ~id) != (client->addr << 1)) {
		dev_err(&client->dev, "Unknown chip ID: %#x\n", id);
		ret = -EINVAL;
		goto err;
	}

	ret = regmap_bulk_read(stmfx->map, STMFX_REG_FW_VERSION_MSB,
			       version, ARRAY_SIZE(version));
	if (ret) {
		dev_err(&client->dev, "Error reading FW version: %d\n", ret);
		goto err;
	}

	dev_info(&client->dev, "STMFX id: %#x, fw version: %x.%02x\n",
		 id, version[0], version[1]);

	ret = stmfx_chip_reset(stmfx);
	if (ret) {
		dev_err(&client->dev, "Failed to reset chip: %d\n", ret);
		goto err;
	}

	return 0;

err:
	if (stmfx->vdd)
		return regulator_disable(stmfx->vdd);

	return ret;
}