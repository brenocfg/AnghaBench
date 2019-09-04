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
struct pm80x_platform_data {int /*<<< orphan*/  (* plat_config ) (struct pm80x_chip*,struct pm80x_platform_data*) ;} ;
struct pm80x_chip {int /*<<< orphan*/ * dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pm80x_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int device_805_init (struct pm80x_chip*) ; 
 struct pm80x_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm80x_deinit () ; 
 int pm80x_init (struct i2c_client*) ; 
 int /*<<< orphan*/  stub1 (struct pm80x_chip*,struct pm80x_platform_data*) ; 

__attribute__((used)) static int pm805_probe(struct i2c_client *client,
				 const struct i2c_device_id *id)
{
	int ret = 0;
	struct pm80x_chip *chip;
	struct pm80x_platform_data *pdata = dev_get_platdata(&client->dev);

	ret = pm80x_init(client);
	if (ret) {
		dev_err(&client->dev, "pm805_init fail!\n");
		goto out_init;
	}

	chip = i2c_get_clientdata(client);

	ret = device_805_init(chip);
	if (ret) {
		dev_err(chip->dev, "Failed to initialize 88pm805 devices\n");
		goto err_805_init;
	}

	if (pdata && pdata->plat_config)
		pdata->plat_config(chip, pdata);

err_805_init:
	pm80x_deinit();
out_init:
	return ret;
}