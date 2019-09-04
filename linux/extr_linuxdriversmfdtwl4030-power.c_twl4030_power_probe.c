#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct twl4030_power_data {int dummy; } ;
struct TYPE_4__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct twl4030_power_data* data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEQ_OFFSYNC ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_CFG_P123_TRANSITION ; 
 int TWL4030_PM_MASTER_KEY_CFG1 ; 
 int TWL4030_PM_MASTER_KEY_CFG2 ; 
 int /*<<< orphan*/  TWL4030_PM_MASTER_PROTECT_KEY ; 
 int /*<<< orphan*/  TWL_MODULE_PM_MASTER ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct twl4030_power_data* dev_get_platdata (TYPE_1__*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ pm_power_off ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int twl4030_power_configure_resources (struct twl4030_power_data const*) ; 
 int twl4030_power_configure_scripts (struct twl4030_power_data const*) ; 
 int /*<<< orphan*/  twl4030_power_of_match ; 
 scalar_t__ twl4030_power_off ; 
 scalar_t__ twl4030_power_use_poweroff (struct twl4030_power_data const*,struct device_node*) ; 
 int twl_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl_i2c_write_u8 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_power_probe(struct platform_device *pdev)
{
	const struct twl4030_power_data *pdata = dev_get_platdata(&pdev->dev);
	struct device_node *node = pdev->dev.of_node;
	const struct of_device_id *match;
	int err = 0;
	int err2 = 0;
	u8 val;

	if (!pdata && !node) {
		dev_err(&pdev->dev, "Platform data is missing\n");
		return -EINVAL;
	}

	err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, TWL4030_PM_MASTER_KEY_CFG1,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	err |= twl_i2c_write_u8(TWL_MODULE_PM_MASTER,
			       TWL4030_PM_MASTER_KEY_CFG2,
			       TWL4030_PM_MASTER_PROTECT_KEY);

	if (err) {
		pr_err("TWL4030 Unable to unlock registers\n");
		return err;
	}

	match = of_match_device(of_match_ptr(twl4030_power_of_match),
				&pdev->dev);
	if (match && match->data)
		pdata = match->data;

	if (pdata) {
		err = twl4030_power_configure_scripts(pdata);
		if (err) {
			pr_err("TWL4030 failed to load scripts\n");
			goto relock;
		}
		err = twl4030_power_configure_resources(pdata);
		if (err) {
			pr_err("TWL4030 failed to configure resource\n");
			goto relock;
		}
	}

	/* Board has to be wired properly to use this feature */
	if (twl4030_power_use_poweroff(pdata, node) && !pm_power_off) {
		/* Default for SEQ_OFFSYNC is set, lets ensure this */
		err = twl_i2c_read_u8(TWL_MODULE_PM_MASTER, &val,
				      TWL4030_PM_MASTER_CFG_P123_TRANSITION);
		if (err) {
			pr_warn("TWL4030 Unable to read registers\n");
		} else if (!(val & SEQ_OFFSYNC)) {
			val |= SEQ_OFFSYNC;
			err = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, val,
					TWL4030_PM_MASTER_CFG_P123_TRANSITION);
			if (err) {
				pr_err("TWL4030 Unable to setup SEQ_OFFSYNC\n");
				goto relock;
			}
		}

		pm_power_off = twl4030_power_off;
	}

relock:
	err2 = twl_i2c_write_u8(TWL_MODULE_PM_MASTER, 0,
			       TWL4030_PM_MASTER_PROTECT_KEY);
	if (err2) {
		pr_err("TWL4030 Unable to relock registers\n");
		return err2;
	}

	return err;
}