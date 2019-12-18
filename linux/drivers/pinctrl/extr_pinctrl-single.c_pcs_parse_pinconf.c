#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long* configs; int num_configs; int /*<<< orphan*/  group_or_pin; } ;
struct TYPE_4__ {TYPE_1__ configs; } ;
struct pinctrl_map {TYPE_2__ data; int /*<<< orphan*/  type; } ;
struct pcs_function {int nconfs; struct pcs_conf_vals* conf; } ;
struct pcs_device {int /*<<< orphan*/  dev; } ;
struct pcs_conf_vals {int dummy; } ;
struct pcs_conf_type {char* member_0; int /*<<< orphan*/  param; int /*<<< orphan*/  name; int /*<<< orphan*/  member_1; } ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct pcs_conf_type const*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCS_HAS_PINCONF ; 
#define  PIN_CONFIG_BIAS_PULL_DOWN 134 
#define  PIN_CONFIG_BIAS_PULL_UP 133 
#define  PIN_CONFIG_DRIVE_STRENGTH 132 
#define  PIN_CONFIG_INPUT_SCHMITT 131 
#define  PIN_CONFIG_INPUT_SCHMITT_ENABLE 130 
#define  PIN_CONFIG_LOW_POWER_MODE 129 
#define  PIN_CONFIG_SLEW_RATE 128 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_GROUP ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_find_property (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcs_add_conf2 (struct pcs_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcs_conf_vals**,unsigned long**) ; 
 int /*<<< orphan*/  pcs_add_conf4 (struct pcs_device*,struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pcs_conf_vals**,unsigned long**) ; 

__attribute__((used)) static int pcs_parse_pinconf(struct pcs_device *pcs, struct device_node *np,
			     struct pcs_function *func,
			     struct pinctrl_map **map)

{
	struct pinctrl_map *m = *map;
	int i = 0, nconfs = 0;
	unsigned long *settings = NULL, *s = NULL;
	struct pcs_conf_vals *conf = NULL;
	static const struct pcs_conf_type prop2[] = {
		{ "pinctrl-single,drive-strength", PIN_CONFIG_DRIVE_STRENGTH, },
		{ "pinctrl-single,slew-rate", PIN_CONFIG_SLEW_RATE, },
		{ "pinctrl-single,input-schmitt", PIN_CONFIG_INPUT_SCHMITT, },
		{ "pinctrl-single,low-power-mode", PIN_CONFIG_LOW_POWER_MODE, },
	};
	static const struct pcs_conf_type prop4[] = {
		{ "pinctrl-single,bias-pullup", PIN_CONFIG_BIAS_PULL_UP, },
		{ "pinctrl-single,bias-pulldown", PIN_CONFIG_BIAS_PULL_DOWN, },
		{ "pinctrl-single,input-schmitt-enable",
			PIN_CONFIG_INPUT_SCHMITT_ENABLE, },
	};

	/* If pinconf isn't supported, don't parse properties in below. */
	if (!PCS_HAS_PINCONF)
		return 0;

	/* cacluate how much properties are supported in current node */
	for (i = 0; i < ARRAY_SIZE(prop2); i++) {
		if (of_find_property(np, prop2[i].name, NULL))
			nconfs++;
	}
	for (i = 0; i < ARRAY_SIZE(prop4); i++) {
		if (of_find_property(np, prop4[i].name, NULL))
			nconfs++;
	}
	if (!nconfs)
		return 0;

	func->conf = devm_kcalloc(pcs->dev,
				  nconfs, sizeof(struct pcs_conf_vals),
				  GFP_KERNEL);
	if (!func->conf)
		return -ENOMEM;
	func->nconfs = nconfs;
	conf = &(func->conf[0]);
	m++;
	settings = devm_kcalloc(pcs->dev, nconfs, sizeof(unsigned long),
				GFP_KERNEL);
	if (!settings)
		return -ENOMEM;
	s = &settings[0];

	for (i = 0; i < ARRAY_SIZE(prop2); i++)
		pcs_add_conf2(pcs, np, prop2[i].name, prop2[i].param,
			      &conf, &s);
	for (i = 0; i < ARRAY_SIZE(prop4); i++)
		pcs_add_conf4(pcs, np, prop4[i].name, prop4[i].param,
			      &conf, &s);
	m->type = PIN_MAP_TYPE_CONFIGS_GROUP;
	m->data.configs.group_or_pin = np->name;
	m->data.configs.configs = settings;
	m->data.configs.num_configs = nconfs;
	return 0;
}