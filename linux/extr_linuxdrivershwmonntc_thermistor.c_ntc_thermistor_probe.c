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
struct thermal_zone_device {scalar_t__ pullup_uv; scalar_t__ pullup_ohm; scalar_t__ connect; scalar_t__ pulldown_ohm; int /*<<< orphan*/ * read_uv; scalar_t__ read_ohm; } ;
struct platform_device_id {int driver_data; int /*<<< orphan*/  name; } ;
struct platform_device {struct thermal_zone_device dev; } ;
struct of_device_id {struct platform_device_id* data; } ;
struct ntc_thermistor_platform_data {scalar_t__ pullup_uv; scalar_t__ pullup_ohm; scalar_t__ connect; scalar_t__ pulldown_ohm; int /*<<< orphan*/ * read_uv; scalar_t__ read_ohm; } ;
struct ntc_data {void* n_comp; void* comp; struct thermal_zone_device* pdata; } ;
struct device {scalar_t__ pullup_uv; scalar_t__ pullup_ohm; scalar_t__ connect; scalar_t__ pulldown_ohm; int /*<<< orphan*/ * read_uv; scalar_t__ read_ohm; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 scalar_t__ NTC_CONNECTED_GROUND ; 
 scalar_t__ NTC_CONNECTED_POSITIVE ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
#define  TYPE_B57330V2103 132 
#define  TYPE_NCPXXWB473 131 
#define  TYPE_NCPXXWF104 130 
#define  TYPE_NCPXXWL333 129 
#define  TYPE_NCPXXXH103 128 
 void* b57330v2103 ; 
 int /*<<< orphan*/  dev_dbg (struct thermal_zone_device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct thermal_zone_device*,char*,...) ; 
 struct thermal_zone_device* dev_get_platdata (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_info (struct thermal_zone_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct thermal_zone_device*,char*) ; 
 struct thermal_zone_device* devm_hwmon_device_register_with_groups (struct thermal_zone_device*,int /*<<< orphan*/ ,struct ntc_data*,int /*<<< orphan*/ ) ; 
 struct ntc_data* devm_kzalloc (struct thermal_zone_device*,int,int /*<<< orphan*/ ) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (struct thermal_zone_device*,int /*<<< orphan*/ ,struct ntc_data*,int /*<<< orphan*/ *) ; 
 void* ncpXXwb473 ; 
 void* ncpXXwf104 ; 
 void* ncpXXwl333 ; 
 void* ncpXXxh103 ; 
 int /*<<< orphan*/  ntc_groups ; 
 int /*<<< orphan*/  ntc_match ; 
 int /*<<< orphan*/  ntc_of_thermal_ops ; 
 struct thermal_zone_device* ntc_thermistor_parse_dt (struct thermal_zone_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct thermal_zone_device*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static int ntc_thermistor_probe(struct platform_device *pdev)
{
	struct thermal_zone_device *tz;
	struct device *dev = &pdev->dev;
	const struct of_device_id *of_id =
			of_match_device(of_match_ptr(ntc_match), dev);
	const struct platform_device_id *pdev_id;
	struct ntc_thermistor_platform_data *pdata;
	struct device *hwmon_dev;
	struct ntc_data *data;

	pdata = ntc_thermistor_parse_dt(dev);
	if (IS_ERR(pdata))
		return PTR_ERR(pdata);
	else if (pdata == NULL)
		pdata = dev_get_platdata(dev);

	if (!pdata) {
		dev_err(dev, "No platform init data supplied.\n");
		return -ENODEV;
	}

	/* Either one of the two is required. */
	if (!pdata->read_uv && !pdata->read_ohm) {
		dev_err(dev,
			"Both read_uv and read_ohm missing. Need either one of the two.\n");
		return -EINVAL;
	}

	if (pdata->read_uv && pdata->read_ohm) {
		dev_warn(dev,
			 "Only one of read_uv and read_ohm is needed; ignoring read_uv.\n");
		pdata->read_uv = NULL;
	}

	if (pdata->read_uv && (pdata->pullup_uv == 0 ||
				(pdata->pullup_ohm == 0 && pdata->connect ==
				 NTC_CONNECTED_GROUND) ||
				(pdata->pulldown_ohm == 0 && pdata->connect ==
				 NTC_CONNECTED_POSITIVE) ||
				(pdata->connect != NTC_CONNECTED_POSITIVE &&
				 pdata->connect != NTC_CONNECTED_GROUND))) {
		dev_err(dev, "Required data to use read_uv not supplied.\n");
		return -EINVAL;
	}

	data = devm_kzalloc(dev, sizeof(struct ntc_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	pdev_id = of_id ? of_id->data : platform_get_device_id(pdev);

	data->pdata = pdata;

	switch (pdev_id->driver_data) {
	case TYPE_NCPXXWB473:
		data->comp = ncpXXwb473;
		data->n_comp = ARRAY_SIZE(ncpXXwb473);
		break;
	case TYPE_NCPXXWL333:
		data->comp = ncpXXwl333;
		data->n_comp = ARRAY_SIZE(ncpXXwl333);
		break;
	case TYPE_B57330V2103:
		data->comp = b57330v2103;
		data->n_comp = ARRAY_SIZE(b57330v2103);
		break;
	case TYPE_NCPXXWF104:
		data->comp = ncpXXwf104;
		data->n_comp = ARRAY_SIZE(ncpXXwf104);
		break;
	case TYPE_NCPXXXH103:
		data->comp = ncpXXxh103;
		data->n_comp = ARRAY_SIZE(ncpXXxh103);
		break;
	default:
		dev_err(dev, "Unknown device type: %lu(%s)\n",
				pdev_id->driver_data, pdev_id->name);
		return -EINVAL;
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, pdev_id->name,
							   data, ntc_groups);
	if (IS_ERR(hwmon_dev)) {
		dev_err(dev, "unable to register as hwmon device.\n");
		return PTR_ERR(hwmon_dev);
	}

	dev_info(dev, "Thermistor type: %s successfully probed.\n",
		 pdev_id->name);

	tz = devm_thermal_zone_of_sensor_register(dev, 0, data,
						  &ntc_of_thermal_ops);
	if (IS_ERR(tz))
		dev_dbg(dev, "Failed to register to thermal fw.\n");

	return 0;
}