#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sch5627_data {int control; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  addr; int /*<<< orphan*/  watchdog; int /*<<< orphan*/ * hwmon_dev; int /*<<< orphan*/  last_battery; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVNAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int SCH5627_COMPANY_ID ; 
 int SCH5627_HWMON_ID ; 
 int SCH5627_PRIMARY_ID ; 
 int /*<<< orphan*/  SCH5627_REG_BUILD_CODE ; 
 int /*<<< orphan*/  SCH5627_REG_BUILD_ID ; 
 int /*<<< orphan*/  SCH5627_REG_COMPANY_ID ; 
 int /*<<< orphan*/  SCH5627_REG_CTRL ; 
 int /*<<< orphan*/  SCH5627_REG_HWMON_ID ; 
 int /*<<< orphan*/  SCH5627_REG_HWMON_REV ; 
 int /*<<< orphan*/  SCH5627_REG_PRIMARY_ID ; 
 struct sch5627_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sch5627_data*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int,int,...) ; 
 int /*<<< orphan*/  sch5627_group ; 
 int sch5627_read_limits (struct sch5627_data*) ; 
 int /*<<< orphan*/  sch5627_remove (struct platform_device*) ; 
 int sch56xx_read_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sch56xx_read_virtual_reg16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sch56xx_watchdog_register (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sch56xx_write_virtual_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sch5627_probe(struct platform_device *pdev)
{
	struct sch5627_data *data;
	int err, build_code, build_id, hwmon_rev, val;

	data = devm_kzalloc(&pdev->dev, sizeof(struct sch5627_data),
			    GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->addr = platform_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platform_set_drvdata(pdev, data);

	val = sch56xx_read_virtual_reg(data->addr, SCH5627_REG_HWMON_ID);
	if (val < 0) {
		err = val;
		goto error;
	}
	if (val != SCH5627_HWMON_ID) {
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "hwmon",
		       val, SCH5627_HWMON_ID);
		err = -ENODEV;
		goto error;
	}

	val = sch56xx_read_virtual_reg(data->addr, SCH5627_REG_COMPANY_ID);
	if (val < 0) {
		err = val;
		goto error;
	}
	if (val != SCH5627_COMPANY_ID) {
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "company",
		       val, SCH5627_COMPANY_ID);
		err = -ENODEV;
		goto error;
	}

	val = sch56xx_read_virtual_reg(data->addr, SCH5627_REG_PRIMARY_ID);
	if (val < 0) {
		err = val;
		goto error;
	}
	if (val != SCH5627_PRIMARY_ID) {
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "primary",
		       val, SCH5627_PRIMARY_ID);
		err = -ENODEV;
		goto error;
	}

	build_code = sch56xx_read_virtual_reg(data->addr,
					      SCH5627_REG_BUILD_CODE);
	if (build_code < 0) {
		err = build_code;
		goto error;
	}

	build_id = sch56xx_read_virtual_reg16(data->addr,
					      SCH5627_REG_BUILD_ID);
	if (build_id < 0) {
		err = build_id;
		goto error;
	}

	hwmon_rev = sch56xx_read_virtual_reg(data->addr,
					     SCH5627_REG_HWMON_REV);
	if (hwmon_rev < 0) {
		err = hwmon_rev;
		goto error;
	}

	val = sch56xx_read_virtual_reg(data->addr, SCH5627_REG_CTRL);
	if (val < 0) {
		err = val;
		goto error;
	}
	data->control = val;
	if (!(data->control & 0x01)) {
		pr_err("hardware monitoring not enabled\n");
		err = -ENODEV;
		goto error;
	}
	/* Trigger a Vbat voltage measurement, so that we get a valid reading
	   the first time we read Vbat */
	sch56xx_write_virtual_reg(data->addr, SCH5627_REG_CTRL,
				  data->control | 0x10);
	data->last_battery = jiffies;

	/*
	 * Read limits, we do this only once as reading a register on
	 * the sch5627 is quite expensive (and they don't change).
	 */
	err = sch5627_read_limits(data);
	if (err)
		goto error;

	pr_info("found %s chip at %#hx\n", DEVNAME, data->addr);
	pr_info("firmware build: code 0x%02X, id 0x%04X, hwmon: rev 0x%02X\n",
		build_code, build_id, hwmon_rev);

	/* Register sysfs interface files */
	err = sysfs_create_group(&pdev->dev.kobj, &sch5627_group);
	if (err)
		goto error;

	data->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = NULL;
		goto error;
	}

	/* Note failing to register the watchdog is not a fatal error */
	data->watchdog = sch56xx_watchdog_register(&pdev->dev, data->addr,
			(build_code << 24) | (build_id << 8) | hwmon_rev,
			&data->update_lock, 1);

	return 0;

error:
	sch5627_remove(pdev);
	return err;
}