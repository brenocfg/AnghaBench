#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct vexpress_syscfg_func {int num_templates; void* regmap; int /*<<< orphan*/  list; int /*<<< orphan*/ * template; struct vexpress_syscfg* syscfg; } ;
struct vexpress_syscfg {int /*<<< orphan*/  funcs; } ;
typedef  void regmap ;
struct property {int length; int /*<<< orphan*/ * value; } ;
struct device {int /*<<< orphan*/  of_node; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_3__ {int max_register; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  SYS_CFGCTRL_DCC (scalar_t__) ; 
 int /*<<< orphan*/  SYS_CFGCTRL_DEVICE (scalar_t__) ; 
 int /*<<< orphan*/  SYS_CFGCTRL_FUNC (scalar_t__) ; 
 int /*<<< orphan*/  SYS_CFGCTRL_POSITION (scalar_t__) ; 
 int /*<<< orphan*/  SYS_CFGCTRL_SITE (scalar_t__) ; 
 scalar_t__ be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,struct vexpress_syscfg_func*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct vexpress_syscfg_func*) ; 
 struct vexpress_syscfg_func* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct property* of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 void* regmap_init (struct device*,int /*<<< orphan*/ *,struct vexpress_syscfg_func*,TYPE_1__*) ; 
 int /*<<< orphan*/  struct_size (struct vexpress_syscfg_func*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  template ; 
 int vexpress_config_get_topo (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 TYPE_1__ vexpress_syscfg_regmap_config ; 

__attribute__((used)) static struct regmap *vexpress_syscfg_regmap_init(struct device *dev,
		void *context)
{
	int err;
	struct vexpress_syscfg *syscfg = context;
	struct vexpress_syscfg_func *func;
	struct property *prop;
	const __be32 *val = NULL;
	__be32 energy_quirk[4];
	int num;
	u32 site, position, dcc;
	int i;

	err = vexpress_config_get_topo(dev->of_node, &site,
				&position, &dcc);
	if (err)
		return ERR_PTR(err);

	prop = of_find_property(dev->of_node,
			"arm,vexpress-sysreg,func", NULL);
	if (!prop)
		return ERR_PTR(-EINVAL);

	num = prop->length / sizeof(u32) / 2;
	val = prop->value;

	/*
	 * "arm,vexpress-energy" function used to be described
	 * by its first device only, now it requires both
	 */
	if (num == 1 && of_device_is_compatible(dev->of_node,
			"arm,vexpress-energy")) {
		num = 2;
		energy_quirk[0] = *val;
		energy_quirk[2] = *val++;
		energy_quirk[1] = *val;
		energy_quirk[3] = cpu_to_be32(be32_to_cpup(val) + 1);
		val = energy_quirk;
	}

	func = kzalloc(struct_size(func, template, num), GFP_KERNEL);
	if (!func)
		return ERR_PTR(-ENOMEM);

	func->syscfg = syscfg;
	func->num_templates = num;

	for (i = 0; i < num; i++) {
		u32 function, device;

		function = be32_to_cpup(val++);
		device = be32_to_cpup(val++);

		dev_dbg(dev, "func %p: %u/%u/%u/%u/%u\n",
				func, site, position, dcc,
				function, device);

		func->template[i] = SYS_CFGCTRL_DCC(dcc);
		func->template[i] |= SYS_CFGCTRL_SITE(site);
		func->template[i] |= SYS_CFGCTRL_POSITION(position);
		func->template[i] |= SYS_CFGCTRL_FUNC(function);
		func->template[i] |= SYS_CFGCTRL_DEVICE(device);
	}

	vexpress_syscfg_regmap_config.max_register = num - 1;

	func->regmap = regmap_init(dev, NULL, func,
			&vexpress_syscfg_regmap_config);

	if (IS_ERR(func->regmap)) {
		void *err = func->regmap;

		kfree(func);
		return err;
	}

	list_add(&func->list, &syscfg->funcs);

	return func->regmap;
}