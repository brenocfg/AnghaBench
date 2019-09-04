#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct k8temp_data {int swap_core_select; int temp_offset; int sensorsp; char* name; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct TYPE_10__ {int x86_model; int x86_stepping; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_TEMP ; 
 int SEL_CORE ; 
 int SEL_PLACE ; 
 TYPE_5__ boot_cpu_data ; 
 int /*<<< orphan*/  dev_attr_name ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct k8temp_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (int /*<<< orphan*/ *) ; 
 scalar_t__ is_rev_g_desktop (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct k8temp_data*) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__ sensor_dev_attr_temp1_input ; 
 TYPE_3__ sensor_dev_attr_temp2_input ; 
 TYPE_2__ sensor_dev_attr_temp3_input ; 
 TYPE_1__ sensor_dev_attr_temp4_input ; 

__attribute__((used)) static int k8temp_probe(struct pci_dev *pdev,
				  const struct pci_device_id *id)
{
	int err;
	u8 scfg;
	u32 temp;
	u8 model, stepping;
	struct k8temp_data *data;

	data = devm_kzalloc(&pdev->dev, sizeof(struct k8temp_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	model = boot_cpu_data.x86_model;
	stepping = boot_cpu_data.x86_stepping;

	/* feature available since SH-C0, exclude older revisions */
	if ((model == 4 && stepping == 0) ||
	    (model == 5 && stepping <= 1))
		return -ENODEV;

	/*
	 * AMD NPT family 0fh, i.e. RevF and RevG:
	 * meaning of SEL_CORE bit is inverted
	 */
	if (model >= 0x40) {
		data->swap_core_select = 1;
		dev_warn(&pdev->dev,
			 "Temperature readouts might be wrong - check erratum #141\n");
	}

	/*
	 * RevG desktop CPUs (i.e. no socket S1G1 or ASB1 parts) need
	 * additional offset, otherwise reported temperature is below
	 * ambient temperature
	 */
	if (is_rev_g_desktop(model))
		data->temp_offset = 21000;

	pci_read_config_byte(pdev, REG_TEMP, &scfg);
	scfg &= ~(SEL_PLACE | SEL_CORE);	/* Select sensor 0, core0 */
	pci_write_config_byte(pdev, REG_TEMP, scfg);
	pci_read_config_byte(pdev, REG_TEMP, &scfg);

	if (scfg & (SEL_PLACE | SEL_CORE)) {
		dev_err(&pdev->dev, "Configuration bit(s) stuck at 1!\n");
		return -ENODEV;
	}

	scfg |= (SEL_PLACE | SEL_CORE);
	pci_write_config_byte(pdev, REG_TEMP, scfg);

	/* now we know if we can change core and/or sensor */
	pci_read_config_byte(pdev, REG_TEMP, &data->sensorsp);

	if (data->sensorsp & SEL_PLACE) {
		scfg &= ~SEL_CORE;	/* Select sensor 1, core0 */
		pci_write_config_byte(pdev, REG_TEMP, scfg);
		pci_read_config_dword(pdev, REG_TEMP, &temp);
		scfg |= SEL_CORE;	/* prepare for next selection */
		if (!((temp >> 16) & 0xff)) /* if temp is 0 -49C is unlikely */
			data->sensorsp &= ~SEL_PLACE;
	}

	if (data->sensorsp & SEL_CORE) {
		scfg &= ~SEL_PLACE;	/* Select sensor 0, core1 */
		pci_write_config_byte(pdev, REG_TEMP, scfg);
		pci_read_config_dword(pdev, REG_TEMP, &temp);
		if (!((temp >> 16) & 0xff)) /* if temp is 0 -49C is unlikely */
			data->sensorsp &= ~SEL_CORE;
	}

	data->name = "k8temp";
	mutex_init(&data->update_lock);
	pci_set_drvdata(pdev, data);

	/* Register sysfs hooks */
	err = device_create_file(&pdev->dev,
			   &sensor_dev_attr_temp1_input.dev_attr);
	if (err)
		goto exit_remove;

	/* sensor can be changed and reports something */
	if (data->sensorsp & SEL_PLACE) {
		err = device_create_file(&pdev->dev,
				   &sensor_dev_attr_temp2_input.dev_attr);
		if (err)
			goto exit_remove;
	}

	/* core can be changed and reports something */
	if (data->sensorsp & SEL_CORE) {
		err = device_create_file(&pdev->dev,
				   &sensor_dev_attr_temp3_input.dev_attr);
		if (err)
			goto exit_remove;
		if (data->sensorsp & SEL_PLACE) {
			err = device_create_file(&pdev->dev,
					   &sensor_dev_attr_temp4_input.
					   dev_attr);
			if (err)
				goto exit_remove;
		}
	}

	err = device_create_file(&pdev->dev, &dev_attr_name);
	if (err)
		goto exit_remove;

	data->hwmon_dev = hwmon_device_register(&pdev->dev);

	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp1_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp2_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp3_input.dev_attr);
	device_remove_file(&pdev->dev,
			   &sensor_dev_attr_temp4_input.dev_attr);
	device_remove_file(&pdev->dev, &dev_attr_name);
	return err;
}