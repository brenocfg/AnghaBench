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
struct soc_device_data {int (* check ) (struct device*) ;struct soc_button_info* button_info; } ;
struct device {int dummy; } ;
struct soc_button_info {struct device dev; } ;
struct soc_button_data {struct soc_button_info const** children; } ;
typedef  struct platform_device {struct device dev; } const platform_device ;

/* Variables and functions */
 int BUTTON_TYPES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct soc_button_info const*) ; 
 int PTR_ERR (struct soc_button_info const*) ; 
 struct soc_device_data* acpi_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  devm_kfree (struct device*,struct soc_button_info const*) ; 
 struct soc_button_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int gpiod_count (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct soc_button_info const*,struct soc_button_data*) ; 
 struct soc_button_info* soc_button_device_create (struct soc_button_info const*,struct soc_button_info const*,int) ; 
 struct soc_button_info* soc_button_get_button_info (struct device*) ; 
 int /*<<< orphan*/  soc_button_remove (struct soc_button_info const*) ; 
 int stub1 (struct device*) ; 

__attribute__((used)) static int soc_button_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct soc_device_data *device_data;
	const struct soc_button_info *button_info;
	struct soc_button_data *priv;
	struct platform_device *pd;
	int i;
	int error;

	device_data = acpi_device_get_match_data(dev);
	if (device_data && device_data->check) {
		error = device_data->check(dev);
		if (error)
			return error;
	}

	if (device_data && device_data->button_info) {
		button_info = device_data->button_info;
	} else {
		button_info = soc_button_get_button_info(dev);
		if (IS_ERR(button_info))
			return PTR_ERR(button_info);
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

	if (!device_data || !device_data->button_info)
		devm_kfree(dev, button_info);

	return 0;
}