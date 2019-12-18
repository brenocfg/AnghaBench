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
typedef  int /*<<< orphan*/  u32 ;
struct imx_pinctrl_soc_info {int flags; scalar_t__ generic_pinconf; } ;
struct imx_pinctrl {int /*<<< orphan*/  dev; struct imx_pinctrl_soc_info* info; } ;
struct imx_pin {int dummy; } ;
struct group_desc {int num_pins; int /*<<< orphan*/ * pins; void* data; int /*<<< orphan*/  name; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FSL_PIN_SHARE_SIZE ; 
 int FSL_PIN_SIZE ; 
 int FSL_SCU_PIN_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IMX_USE_SCU ; 
 int SHARE_MUX_CONF_REG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct device_node*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_pinctrl_parse_pin_mmio (struct imx_pinctrl*,int /*<<< orphan*/ *,struct imx_pin*,int /*<<< orphan*/  const**,struct device_node*) ; 
 int /*<<< orphan*/  imx_pinctrl_parse_pin_scu (struct imx_pinctrl*,int /*<<< orphan*/ *,struct imx_pin*,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 

__attribute__((used)) static int imx_pinctrl_parse_groups(struct device_node *np,
				    struct group_desc *grp,
				    struct imx_pinctrl *ipctl,
				    u32 index)
{
	const struct imx_pinctrl_soc_info *info = ipctl->info;
	struct imx_pin *pin;
	int size, pin_size;
	const __be32 *list;
	int i;

	dev_dbg(ipctl->dev, "group(%d): %pOFn\n", index, np);

	if (info->flags & IMX_USE_SCU)
		pin_size = FSL_SCU_PIN_SIZE;
	else if (info->flags & SHARE_MUX_CONF_REG)
		pin_size = FSL_PIN_SHARE_SIZE;
	else
		pin_size = FSL_PIN_SIZE;

	if (info->generic_pinconf)
		pin_size -= 4;

	/* Initialise group */
	grp->name = np->name;

	/*
	 * the binding format is fsl,pins = <PIN_FUNC_ID CONFIG ...>,
	 * do sanity check and calculate pins number
	 *
	 * First try legacy 'fsl,pins' property, then fall back to the
	 * generic 'pinmux'.
	 *
	 * Note: for generic 'pinmux' case, there's no CONFIG part in
	 * the binding format.
	 */
	list = of_get_property(np, "fsl,pins", &size);
	if (!list) {
		list = of_get_property(np, "pinmux", &size);
		if (!list) {
			dev_err(ipctl->dev,
				"no fsl,pins and pins property in node %pOF\n", np);
			return -EINVAL;
		}
	}

	/* we do not check return since it's safe node passed down */
	if (!size || size % pin_size) {
		dev_err(ipctl->dev, "Invalid fsl,pins or pins property in node %pOF\n", np);
		return -EINVAL;
	}

	grp->num_pins = size / pin_size;
	grp->data = devm_kcalloc(ipctl->dev,
				 grp->num_pins, sizeof(struct imx_pin),
				 GFP_KERNEL);
	grp->pins = devm_kcalloc(ipctl->dev,
				 grp->num_pins, sizeof(unsigned int),
				 GFP_KERNEL);
	if (!grp->pins || !grp->data)
		return -ENOMEM;

	for (i = 0; i < grp->num_pins; i++) {
		pin = &((struct imx_pin *)(grp->data))[i];
		if (info->flags & IMX_USE_SCU)
			imx_pinctrl_parse_pin_scu(ipctl, &grp->pins[i],
						  pin, &list);
		else
			imx_pinctrl_parse_pin_mmio(ipctl, &grp->pins[i],
						   pin, &list, np);
	}

	return 0;
}