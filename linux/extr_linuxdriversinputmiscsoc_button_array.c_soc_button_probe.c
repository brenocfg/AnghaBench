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
struct device {TYPE_1__* driver; } ;
struct soc_button_info {struct device dev; } ;
struct soc_button_data {struct soc_button_info** children; } ;
struct platform_device {struct device dev; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int BUTTON_TYPES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct soc_button_info*) ; 
 int PTR_ERR (struct soc_button_info*) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct soc_button_info*) ; 
 struct soc_button_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiod_count (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct soc_button_info*,struct soc_button_data*) ; 
 struct soc_button_info* soc_button_device_create (struct soc_button_info*,struct soc_button_info*,int) ; 
 struct soc_button_info* soc_button_get_button_info (struct device*) ; 
 int /*<<< orphan*/  soc_button_remove (struct soc_button_info*) ; 

__attribute__((used)) static int soc_button_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct acpi_device_id *id;
	struct soc_button_info *button_info;
	struct soc_button_data *priv;
	struct platform_device *pd;
	int i;
	int error;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	if (!id)
		return -ENODEV;

	if (!id->driver_data) {
		button_info = soc_button_get_button_info(dev);
		if (IS_ERR(button_info))
			return PTR_ERR(button_info);
	} else {
		button_info = (struct soc_button_info *)id->driver_data;
	}

	error = gpiod_count(dev, NULL);
	if (error < 0) {
		dev_dbg(dev, "no GPIO attached, ignoring...\n");
		return -ENODEV;
	}

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	platform_set_drvdata(pdev, priv);

	for (i = 0; i < BUTTON_TYPES; i++) {
		pd = soc_button_device_create(pdev, button_info, i == 0);
		if (IS_ERR(pd)) {
			error = PTR_ERR(pd);
			if (error != -ENODEV) {
				soc_button_remove(pdev);
				return error;
			}
			continue;
		}

		priv->children[i] = pd;
	}

	if (!priv->children[0] && !priv->children[1])
		return -ENODEV;

	if (!id->driver_data)
		devm_kfree(dev, button_info);

	return 0;
}