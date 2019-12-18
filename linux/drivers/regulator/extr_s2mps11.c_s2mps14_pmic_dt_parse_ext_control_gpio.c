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
struct s2mps11_info {struct gpio_desc** ext_control_gpiod; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_regulator_match {int /*<<< orphan*/  name; int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int /*<<< orphan*/  ENOENT ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  PTR_ERR (struct gpio_desc*) ; 
 unsigned int S2MPS14_LDO10 ; 
 unsigned int S2MPS14_LDO11 ; 
 unsigned int S2MPS14_LDO12 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 struct gpio_desc* devm_gpiod_get_from_of_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void s2mps14_pmic_dt_parse_ext_control_gpio(struct platform_device *pdev,
		struct of_regulator_match *rdata, struct s2mps11_info *s2mps11)
{
	struct gpio_desc **gpio = s2mps11->ext_control_gpiod;
	unsigned int i;
	unsigned int valid_regulators[3] = { S2MPS14_LDO10, S2MPS14_LDO11,
		S2MPS14_LDO12 };

	for (i = 0; i < ARRAY_SIZE(valid_regulators); i++) {
		unsigned int reg = valid_regulators[i];

		if (!rdata[reg].init_data || !rdata[reg].of_node)
			continue;

		gpio[reg] = devm_gpiod_get_from_of_node(&pdev->dev,
				rdata[reg].of_node,
				"samsung,ext-control-gpios",
				0,
				GPIOD_OUT_HIGH | GPIOD_FLAGS_BIT_NONEXCLUSIVE,
				"s2mps11-regulator");
		if (PTR_ERR(gpio[reg]) == -ENOENT)
			gpio[reg] = NULL;
		else if (IS_ERR(gpio[reg])) {
			dev_err(&pdev->dev, "Failed to get control GPIO for %d/%s\n",
				reg, rdata[reg].name);
			gpio[reg] = NULL;
			continue;
		}
		if (gpio[reg])
			dev_dbg(&pdev->dev, "Using GPIO for ext-control over %d/%s\n",
				reg, rdata[reg].name);
	}
}