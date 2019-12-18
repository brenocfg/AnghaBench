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
typedef  int u32 ;
struct TYPE_4__ {unsigned long* configs; int num_configs; int /*<<< orphan*/  group_or_pin; } ;
struct TYPE_5__ {TYPE_1__ configs; } ;
struct pinctrl_map {TYPE_2__ data; int /*<<< orphan*/  type; } ;
struct device_node {int dummy; } ;
struct bcm2835_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_PINCONF_PARAM_PULL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_PIN ; 
 TYPE_3__* bcm2835_gpio_pins ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*,int) ; 
 unsigned long* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned long pinconf_to_config_packed (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2835_pctl_dt_node_to_map_pull(struct bcm2835_pinctrl *pc,
		struct device_node *np, u32 pin, u32 pull,
		struct pinctrl_map **maps)
{
	struct pinctrl_map *map = *maps;
	unsigned long *configs;

	if (pull > 2) {
		dev_err(pc->dev, "%pOF: invalid brcm,pull %d\n", np, pull);
		return -EINVAL;
	}

	configs = kzalloc(sizeof(*configs), GFP_KERNEL);
	if (!configs)
		return -ENOMEM;
	configs[0] = pinconf_to_config_packed(BCM2835_PINCONF_PARAM_PULL, pull);

	map->type = PIN_MAP_TYPE_CONFIGS_PIN;
	map->data.configs.group_or_pin = bcm2835_gpio_pins[pin].name;
	map->data.configs.configs = configs;
	map->data.configs.num_configs = 1;
	(*maps)++;

	return 0;
}