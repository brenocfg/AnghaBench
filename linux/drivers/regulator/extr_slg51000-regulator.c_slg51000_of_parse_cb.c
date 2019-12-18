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
struct slg51000 {int /*<<< orphan*/  dev; } ;
struct regulator_desc {int dummy; } ;
struct regulator_config {struct gpio_desc* ena_gpiod; struct slg51000* driver_data; } ;
struct gpio_desc {int dummy; } ;
struct device_node {int dummy; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  IS_ERR (struct gpio_desc*) ; 
 struct gpio_desc* devm_gpiod_get_from_of_node (int /*<<< orphan*/ ,struct device_node*,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  devm_gpiod_unhinge (int /*<<< orphan*/ ,struct gpio_desc*) ; 

__attribute__((used)) static int slg51000_of_parse_cb(struct device_node *np,
				const struct regulator_desc *desc,
				struct regulator_config *config)
{
	struct slg51000 *chip = config->driver_data;
	struct gpio_desc *ena_gpiod;
	enum gpiod_flags gflags = GPIOD_OUT_LOW | GPIOD_FLAGS_BIT_NONEXCLUSIVE;

	ena_gpiod = devm_gpiod_get_from_of_node(chip->dev, np,
						"enable-gpios", 0,
						gflags, "gpio-en-ldo");
	if (!IS_ERR(ena_gpiod)) {
		config->ena_gpiod = ena_gpiod;
		devm_gpiod_unhinge(chip->dev, config->ena_gpiod);
	}

	return 0;
}