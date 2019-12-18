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
struct pinctrl_dev {int /*<<< orphan*/  mutex; struct device* dev; int /*<<< orphan*/  node; int /*<<< orphan*/  gpio_ranges; int /*<<< orphan*/  pin_function_tree; int /*<<< orphan*/  pin_group_tree; int /*<<< orphan*/  pin_desc_tree; void* driver_data; struct pinctrl_desc* desc; int /*<<< orphan*/  owner; } ;
struct pinctrl_desc {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; scalar_t__ confops; scalar_t__ pmxops; int /*<<< orphan*/  owner; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct pinctrl_dev* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  kfree (struct pinctrl_dev*) ; 
 struct pinctrl_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pinconf_check_ops (struct pinctrl_dev*) ; 
 int pinctrl_check_ops (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  pinctrl_free_pindescs (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pinctrl_register_pins (struct pinctrl_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pinmux_check_ops (struct pinctrl_dev*) ; 

__attribute__((used)) static struct pinctrl_dev *
pinctrl_init_controller(struct pinctrl_desc *pctldesc, struct device *dev,
			void *driver_data)
{
	struct pinctrl_dev *pctldev;
	int ret;

	if (!pctldesc)
		return ERR_PTR(-EINVAL);
	if (!pctldesc->name)
		return ERR_PTR(-EINVAL);

	pctldev = kzalloc(sizeof(*pctldev), GFP_KERNEL);
	if (!pctldev)
		return ERR_PTR(-ENOMEM);

	/* Initialize pin control device struct */
	pctldev->owner = pctldesc->owner;
	pctldev->desc = pctldesc;
	pctldev->driver_data = driver_data;
	INIT_RADIX_TREE(&pctldev->pin_desc_tree, GFP_KERNEL);
#ifdef CONFIG_GENERIC_PINCTRL_GROUPS
	INIT_RADIX_TREE(&pctldev->pin_group_tree, GFP_KERNEL);
#endif
#ifdef CONFIG_GENERIC_PINMUX_FUNCTIONS
	INIT_RADIX_TREE(&pctldev->pin_function_tree, GFP_KERNEL);
#endif
	INIT_LIST_HEAD(&pctldev->gpio_ranges);
	INIT_LIST_HEAD(&pctldev->node);
	pctldev->dev = dev;
	mutex_init(&pctldev->mutex);

	/* check core ops for sanity */
	ret = pinctrl_check_ops(pctldev);
	if (ret) {
		dev_err(dev, "pinctrl ops lacks necessary functions\n");
		goto out_err;
	}

	/* If we're implementing pinmuxing, check the ops for sanity */
	if (pctldesc->pmxops) {
		ret = pinmux_check_ops(pctldev);
		if (ret)
			goto out_err;
	}

	/* If we're implementing pinconfig, check the ops for sanity */
	if (pctldesc->confops) {
		ret = pinconf_check_ops(pctldev);
		if (ret)
			goto out_err;
	}

	/* Register all the pins */
	dev_dbg(dev, "try to register %d pins ...\n",  pctldesc->npins);
	ret = pinctrl_register_pins(pctldev, pctldesc->pins, pctldesc->npins);
	if (ret) {
		dev_err(dev, "error during pin registration\n");
		pinctrl_free_pindescs(pctldev, pctldesc->pins,
				      pctldesc->npins);
		goto out_err;
	}

	return pctldev;

out_err:
	mutex_destroy(&pctldev->mutex);
	kfree(pctldev);
	return ERR_PTR(ret);
}