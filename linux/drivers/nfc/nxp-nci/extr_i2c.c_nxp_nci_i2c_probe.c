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
struct nxp_nci_i2c_phy {int /*<<< orphan*/  ndev; void* gpiod_fw; void* gpiod_en; struct i2c_client* i2c_dev; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  NXP_NCI_I2C_DRIVER_NAME ; 
 int /*<<< orphan*/  NXP_NCI_I2C_MAX_PAYLOAD ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  acpi_nxp_nci_gpios ; 
 int devm_acpi_dev_add_driver_gpios (struct device*,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct nxp_nci_i2c_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_phy_ops ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct nxp_nci_i2c_phy*) ; 
 int /*<<< orphan*/  nfc_err (struct device*,char*) ; 
 int /*<<< orphan*/  nxp_nci_i2c_irq_thread_fn ; 
 int nxp_nci_probe (struct nxp_nci_i2c_phy*,struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct nxp_nci_i2c_phy*) ; 

__attribute__((used)) static int nxp_nci_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct nxp_nci_i2c_phy *phy;
	int r;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		nfc_err(&client->dev, "Need I2C_FUNC_I2C\n");
		return -ENODEV;
	}

	phy = devm_kzalloc(&client->dev, sizeof(struct nxp_nci_i2c_phy),
			   GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	phy->i2c_dev = client;
	i2c_set_clientdata(client, phy);

	r = devm_acpi_dev_add_driver_gpios(dev, acpi_nxp_nci_gpios);
	if (r)
		return r;

	phy->gpiod_en = devm_gpiod_get(dev, "enable", GPIOD_OUT_LOW);
	if (IS_ERR(phy->gpiod_en)) {
		nfc_err(dev, "Failed to get EN gpio\n");
		return PTR_ERR(phy->gpiod_en);
	}

	phy->gpiod_fw = devm_gpiod_get(dev, "firmware", GPIOD_OUT_LOW);
	if (IS_ERR(phy->gpiod_fw)) {
		nfc_err(dev, "Failed to get FW gpio\n");
		return PTR_ERR(phy->gpiod_fw);
	}

	r = nxp_nci_probe(phy, &client->dev, &i2c_phy_ops,
			  NXP_NCI_I2C_MAX_PAYLOAD, &phy->ndev);
	if (r < 0)
		return r;

	r = request_threaded_irq(client->irq, NULL,
				 nxp_nci_i2c_irq_thread_fn,
				 IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				 NXP_NCI_I2C_DRIVER_NAME, phy);
	if (r < 0)
		nfc_err(&client->dev, "Unable to register IRQ handler\n");

	return r;
}