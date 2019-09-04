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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct st33zp24_i2c_phy {int io_lpcpd; } ;
struct st33zp24_dev {struct st33zp24_i2c_phy* phy_id; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  acpi_st33zp24_gpios ; 
 int desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct st33zp24_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct tpm_chip* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int st33zp24_i2c_acpi_request_resources(struct i2c_client *client)
{
	struct tpm_chip *chip = i2c_get_clientdata(client);
	struct st33zp24_dev *tpm_dev = dev_get_drvdata(&chip->dev);
	struct st33zp24_i2c_phy *phy = tpm_dev->phy_id;
	struct gpio_desc *gpiod_lpcpd;
	struct device *dev = &client->dev;
	int ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_st33zp24_gpios);
	if (ret)
		return ret;

	/* Get LPCPD GPIO from ACPI */
	gpiod_lpcpd = devm_gpiod_get(dev, "lpcpd", GPIOD_OUT_HIGH);
	if (IS_ERR(gpiod_lpcpd)) {
		dev_err(&client->dev,
			"Failed to retrieve lpcpd-gpios from acpi.\n");
		phy->io_lpcpd = -1;
		/*
		 * lpcpd pin is not specified. This is not an issue as
		 * power management can be also managed by TPM specific
		 * commands. So leave with a success status code.
		 */
		return 0;
	}

	phy->io_lpcpd = desc_to_gpio(gpiod_lpcpd);

	return 0;
}