#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rockchip_pinctrl {int /*<<< orphan*/  dev; } ;
struct rockchip_pin_group {int npins; TYPE_1__* data; scalar_t__* pins; int /*<<< orphan*/  name; } ;
struct rockchip_pin_config {int dummy; } ;
struct rockchip_pin_bank {scalar_t__ pin_base; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  nconfigs; int /*<<< orphan*/  configs; void* func; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct rockchip_pin_bank*) ; 
 int PTR_ERR (struct rockchip_pin_bank*) ; 
 struct rockchip_pin_bank* bank_num_to_bank (struct rockchip_pinctrl*,int) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 int pinconf_generic_parse_dt_config (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_pinctrl_parse_groups(struct device_node *np,
					      struct rockchip_pin_group *grp,
					      struct rockchip_pinctrl *info,
					      u32 index)
{
	struct rockchip_pin_bank *bank;
	int size;
	const __be32 *list;
	int num;
	int i, j;
	int ret;

	dev_dbg(info->dev, "group(%d): %pOFn\n", index, np);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding format is rockchip,pins = <bank pin mux CONFIG>,
	 * do sanity check and calculate pins number
	 */
	list = of_get_property(np, "rockchip,pins", &size);
	/* we do not check return since it's safe node passed down */
	size /= sizeof(*list);
	if (!size || size % 4) {
		dev_err(info->dev, "wrong pins number or pins and configs should be by 4\n");
		return -EINVAL;
	}

	grp->npins = size / 4;

	grp->pins = devm_kcalloc(info->dev, grp->npins, sizeof(unsigned int),
						GFP_KERNEL);
	grp->data = devm_kcalloc(info->dev,
					grp->npins,
					sizeof(struct rockchip_pin_config),
					GFP_KERNEL);
	if (!grp->pins || !grp->data)
		return -ENOMEM;

	for (i = 0, j = 0; i < size; i += 4, j++) {
		const __be32 *phandle;
		struct device_node *np_config;

		num = be32_to_cpu(*list++);
		bank = bank_num_to_bank(info, num);
		if (IS_ERR(bank))
			return PTR_ERR(bank);

		grp->pins[j] = bank->pin_base + be32_to_cpu(*list++);
		grp->data[j].func = be32_to_cpu(*list++);

		phandle = list++;
		if (!phandle)
			return -EINVAL;

		np_config = of_find_node_by_phandle(be32_to_cpup(phandle));
		ret = pinconf_generic_parse_dt_config(np_config, NULL,
				&grp->data[j].configs, &grp->data[j].nconfigs);
		if (ret)
			return ret;
	}

	return 0;
}