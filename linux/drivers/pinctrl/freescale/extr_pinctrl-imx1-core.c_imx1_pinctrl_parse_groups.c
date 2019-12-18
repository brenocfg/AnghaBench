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
struct imx1_pinctrl_soc_info {int /*<<< orphan*/  dev; } ;
struct imx1_pin_group {int npins; TYPE_1__* pins; void** pin_ids; int /*<<< orphan*/  name; } ;
struct imx1_pin {int dummy; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {void* pin_id; void* config; void* mux_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static int imx1_pinctrl_parse_groups(struct device_node *np,
				    struct imx1_pin_group *grp,
				    struct imx1_pinctrl_soc_info *info,
				    u32 index)
{
	int size;
	const __be32 *list;
	int i;

	dev_dbg(info->dev, "group(%d): %pOFn\n", index, np);

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding format is fsl,pins = <PIN MUX_ID CONFIG>
	 */
	list = of_get_property(np, "fsl,pins", &size);
	/* we do not check return since it's safe node passed down */
	if (!size || size % 12) {
		dev_notice(info->dev, "Not a valid fsl,pins property (%pOFn)\n",
				np);
		return -EINVAL;
	}

	grp->npins = size / 12;
	grp->pins = devm_kcalloc(info->dev,
			grp->npins, sizeof(struct imx1_pin), GFP_KERNEL);
	grp->pin_ids = devm_kcalloc(info->dev,
			grp->npins, sizeof(unsigned int), GFP_KERNEL);

	if (!grp->pins || !grp->pin_ids)
		return -ENOMEM;

	for (i = 0; i < grp->npins; i++) {
		grp->pins[i].pin_id = be32_to_cpu(*list++);
		grp->pins[i].mux_id = be32_to_cpu(*list++);
		grp->pins[i].config = be32_to_cpu(*list++);

		grp->pin_ids[i] = grp->pins[i].pin_id;
	}

	return 0;
}