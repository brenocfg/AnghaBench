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
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct fam15h_power_data {int /*<<< orphan*/ ** groups; int /*<<< orphan*/  group; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct fam15h_power_data*,int /*<<< orphan*/ **) ; 
 struct fam15h_power_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fam15h_power_init_data (struct pci_dev*,struct fam15h_power_data*) ; 
 int /*<<< orphan*/  should_load_on_this_node (struct pci_dev*) ; 
 int /*<<< orphan*/  tweak_runavg_range (struct pci_dev*) ; 

__attribute__((used)) static int fam15h_power_probe(struct pci_dev *pdev,
			      const struct pci_device_id *id)
{
	struct fam15h_power_data *data;
	struct device *dev = &pdev->dev;
	struct device *hwmon_dev;
	int ret;

	/*
	 * though we ignore every other northbridge, we still have to
	 * do the tweaking on _each_ node in MCM processors as the counters
	 * are working hand-in-hand
	 */
	tweak_runavg_range(pdev);

	if (!should_load_on_this_node(pdev))
		return -ENODEV;

	data = devm_kzalloc(dev, sizeof(struct fam15h_power_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	ret = fam15h_power_init_data(pdev, data);
	if (ret)
		return ret;

	data->pdev = pdev;

	data->groups[0] = &data->group;

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, "fam15h_power",
							   data,
							   &data->groups[0]);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}