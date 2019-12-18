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
struct tctl_offset {int model; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; } ;
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct k10temp_data {int temp_adjust_mask; int show_tdie; int /*<<< orphan*/  temp_offset; int /*<<< orphan*/  read_tempreg; int /*<<< orphan*/  read_htcreg; struct pci_dev* pdev; } ;
struct TYPE_2__ {int x86; int x86_model; int /*<<< orphan*/  x86_model_id; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tctl_offset*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct k10temp_data*,int /*<<< orphan*/ ) ; 
 struct k10temp_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force ; 
 int has_erratum_319 (struct pci_dev*) ; 
 int /*<<< orphan*/  k10temp_groups ; 
 int /*<<< orphan*/  read_htcreg_nb_f15 ; 
 int /*<<< orphan*/  read_htcreg_pci ; 
 int /*<<< orphan*/  read_tempreg_nb_f15 ; 
 int /*<<< orphan*/  read_tempreg_nb_f17 ; 
 int /*<<< orphan*/  read_tempreg_pci ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tctl_offset* tctl_offset_table ; 

__attribute__((used)) static int k10temp_probe(struct pci_dev *pdev,
				   const struct pci_device_id *id)
{
	int unreliable = has_erratum_319(pdev);
	struct device *dev = &pdev->dev;
	struct k10temp_data *data;
	struct device *hwmon_dev;
	int i;

	if (unreliable) {
		if (!force) {
			dev_err(dev,
				"unreliable CPU thermal sensor; monitoring disabled\n");
			return -ENODEV;
		}
		dev_warn(dev,
			 "unreliable CPU thermal sensor; check erratum 319\n");
	}

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->pdev = pdev;

	if (boot_cpu_data.x86 == 0x15 &&
	    ((boot_cpu_data.x86_model & 0xf0) == 0x60 ||
	     (boot_cpu_data.x86_model & 0xf0) == 0x70)) {
		data->read_htcreg = read_htcreg_nb_f15;
		data->read_tempreg = read_tempreg_nb_f15;
	} else if (boot_cpu_data.x86 == 0x17 || boot_cpu_data.x86 == 0x18) {
		data->temp_adjust_mask = 0x80000;
		data->read_tempreg = read_tempreg_nb_f17;
		data->show_tdie = true;
	} else {
		data->read_htcreg = read_htcreg_pci;
		data->read_tempreg = read_tempreg_pci;
	}

	for (i = 0; i < ARRAY_SIZE(tctl_offset_table); i++) {
		const struct tctl_offset *entry = &tctl_offset_table[i];

		if (boot_cpu_data.x86 == entry->model &&
		    strstr(boot_cpu_data.x86_model_id, entry->id)) {
			data->temp_offset = entry->offset;
			break;
		}
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, "k10temp", data,
							   k10temp_groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}