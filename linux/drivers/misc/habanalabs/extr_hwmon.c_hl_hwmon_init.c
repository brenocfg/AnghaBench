#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  card_name; } ;
struct asic_fixed_properties {TYPE_2__ armcp_info; } ;
struct hl_device {int hwmon_initialized; struct device* dev; int /*<<< orphan*/  hwmon_dev; TYPE_3__* hl_chip_info; int /*<<< orphan*/  fw_loading; struct asic_fixed_properties asic_prop; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; scalar_t__ info; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hl_hwmon_ops ; 
 int /*<<< orphan*/  hwmon_device_register_with_info (struct device*,int /*<<< orphan*/ ,struct hl_device*,TYPE_3__*,int /*<<< orphan*/ *) ; 

int hl_hwmon_init(struct hl_device *hdev)
{
	struct device *dev = hdev->pdev ? &hdev->pdev->dev : hdev->dev;
	struct asic_fixed_properties *prop = &hdev->asic_prop;
	int rc;

	if ((hdev->hwmon_initialized) || !(hdev->fw_loading))
		return 0;

	if (hdev->hl_chip_info->info) {
		hdev->hl_chip_info->ops = &hl_hwmon_ops;

		hdev->hwmon_dev = hwmon_device_register_with_info(dev,
					prop->armcp_info.card_name, hdev,
					hdev->hl_chip_info, NULL);
		if (IS_ERR(hdev->hwmon_dev)) {
			rc = PTR_ERR(hdev->hwmon_dev);
			dev_err(hdev->dev,
				"Unable to register hwmon device: %d\n", rc);
			return rc;
		}

		dev_info(hdev->dev, "%s: add sensors information\n",
			dev_name(hdev->hwmon_dev));

		hdev->hwmon_initialized = true;
	} else {
		dev_info(hdev->dev, "no available sensors\n");
	}

	return 0;
}