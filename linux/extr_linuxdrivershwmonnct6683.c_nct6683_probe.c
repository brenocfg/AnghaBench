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
struct resource {int /*<<< orphan*/  start; } ;
struct device {struct nct6683_sio_data* platform_data; } ;
struct platform_device {struct device dev; } ;
struct nct6683_sio_data {size_t kind; int /*<<< orphan*/  sioreg; } ;
struct nct6683_data {size_t kind; int customer_id; struct attribute_group** groups; scalar_t__ temp_num; scalar_t__ have_fan; scalar_t__ in_num; scalar_t__ have_pwm; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  addr; int /*<<< orphan*/  sioreg; } ;
struct attribute_group {int dummy; } ;
typedef  int /*<<< orphan*/  build ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOREGION_LENGTH ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (struct attribute_group*) ; 
#define  NCT6683_CUSTOMER_ID_INTEL 129 
#define  NCT6683_CUSTOMER_ID_MITAC 128 
 int /*<<< orphan*/  NCT6683_REG_BUILD_DAY ; 
 int /*<<< orphan*/  NCT6683_REG_BUILD_MONTH ; 
 int /*<<< orphan*/  NCT6683_REG_BUILD_YEAR ; 
 int /*<<< orphan*/  NCT6683_REG_CUSTOMER_ID ; 
 int /*<<< orphan*/  NCT6683_REG_VERSION_HI ; 
 int /*<<< orphan*/  NCT6683_REG_VERSION_LO ; 
 int PTR_ERR (struct attribute_group*) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,int /*<<< orphan*/ ,struct nct6683_data*,struct attribute_group**) ; 
 struct nct6683_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_request_region (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fls (scalar_t__) ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nct6683_chip_names ; 
 struct attribute_group* nct6683_create_attr_group (struct device*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * nct6683_device_names ; 
 int /*<<< orphan*/  nct6683_fan_template_group ; 
 struct attribute_group nct6683_group_other ; 
 int /*<<< orphan*/  nct6683_in_template_group ; 
 int /*<<< orphan*/  nct6683_init_device (struct nct6683_data*) ; 
 int /*<<< orphan*/  nct6683_pwm_template_group ; 
 int /*<<< orphan*/  nct6683_read (struct nct6683_data*,int /*<<< orphan*/ ) ; 
 int nct6683_read16 (struct nct6683_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6683_setup_fans (struct nct6683_data*) ; 
 int /*<<< orphan*/  nct6683_setup_sensors (struct nct6683_data*) ; 
 int /*<<< orphan*/  nct6683_temp_template_group ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct nct6683_data*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nct6683_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct nct6683_sio_data *sio_data = dev->platform_data;
	struct attribute_group *group;
	struct nct6683_data *data;
	struct device *hwmon_dev;
	struct resource *res;
	int groups = 0;
	char build[16];

	res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!devm_request_region(dev, res->start, IOREGION_LENGTH, DRVNAME))
		return -EBUSY;

	data = devm_kzalloc(dev, sizeof(struct nct6683_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->kind = sio_data->kind;
	data->sioreg = sio_data->sioreg;
	data->addr = res->start;
	mutex_init(&data->update_lock);
	platform_set_drvdata(pdev, data);

	data->customer_id = nct6683_read16(data, NCT6683_REG_CUSTOMER_ID);

	/* By default only instantiate driver if the customer ID is known */
	switch (data->customer_id) {
	case NCT6683_CUSTOMER_ID_INTEL:
		break;
	case NCT6683_CUSTOMER_ID_MITAC:
		break;
	default:
		if (!force)
			return -ENODEV;
	}

	nct6683_init_device(data);
	nct6683_setup_fans(data);
	nct6683_setup_sensors(data);

	/* Register sysfs hooks */

	if (data->have_pwm) {
		group = nct6683_create_attr_group(dev,
						  &nct6683_pwm_template_group,
						  fls(data->have_pwm));
		if (IS_ERR(group))
			return PTR_ERR(group);
		data->groups[groups++] = group;
	}

	if (data->in_num) {
		group = nct6683_create_attr_group(dev,
						  &nct6683_in_template_group,
						  data->in_num);
		if (IS_ERR(group))
			return PTR_ERR(group);
		data->groups[groups++] = group;
	}

	if (data->have_fan) {
		group = nct6683_create_attr_group(dev,
						  &nct6683_fan_template_group,
						  fls(data->have_fan));
		if (IS_ERR(group))
			return PTR_ERR(group);
		data->groups[groups++] = group;
	}

	if (data->temp_num) {
		group = nct6683_create_attr_group(dev,
						  &nct6683_temp_template_group,
						  data->temp_num);
		if (IS_ERR(group))
			return PTR_ERR(group);
		data->groups[groups++] = group;
	}
	data->groups[groups++] = &nct6683_group_other;

	if (data->customer_id == NCT6683_CUSTOMER_ID_INTEL)
		scnprintf(build, sizeof(build), "%02x/%02x/%02x",
			  nct6683_read(data, NCT6683_REG_BUILD_MONTH),
			  nct6683_read(data, NCT6683_REG_BUILD_DAY),
			  nct6683_read(data, NCT6683_REG_BUILD_YEAR));
	else
		scnprintf(build, sizeof(build), "%02d/%02d/%02d",
			  nct6683_read(data, NCT6683_REG_BUILD_MONTH),
			  nct6683_read(data, NCT6683_REG_BUILD_DAY),
			  nct6683_read(data, NCT6683_REG_BUILD_YEAR));

	dev_info(dev, "%s EC firmware version %d.%d build %s\n",
		 nct6683_chip_names[data->kind],
		 nct6683_read(data, NCT6683_REG_VERSION_HI),
		 nct6683_read(data, NCT6683_REG_VERSION_LO),
		 build);

	hwmon_dev = devm_hwmon_device_register_with_groups(dev,
			nct6683_device_names[data->kind], data, data->groups);
	return PTR_ERR_OR_ZERO(hwmon_dev);
}