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
struct pinctrl_pin_desc {int /*<<< orphan*/  number; int /*<<< orphan*/  drv_data; scalar_t__ name; } ;
struct pinctrl_dev {TYPE_1__* desc; int /*<<< orphan*/  pin_desc_tree; int /*<<< orphan*/  dev; } ;
struct pin_desc {int dynamic_name; scalar_t__ name; int /*<<< orphan*/  drv_data; struct pinctrl_dev* pctldev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pin_desc*) ; 
 struct pin_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pin_desc*) ; 

__attribute__((used)) static int pinctrl_register_one_pin(struct pinctrl_dev *pctldev,
				    const struct pinctrl_pin_desc *pin)
{
	struct pin_desc *pindesc;

	pindesc = pin_desc_get(pctldev, pin->number);
	if (pindesc) {
		dev_err(pctldev->dev, "pin %d already registered\n",
			pin->number);
		return -EINVAL;
	}

	pindesc = kzalloc(sizeof(*pindesc), GFP_KERNEL);
	if (!pindesc)
		return -ENOMEM;

	/* Set owner */
	pindesc->pctldev = pctldev;

	/* Copy basic pin info */
	if (pin->name) {
		pindesc->name = pin->name;
	} else {
		pindesc->name = kasprintf(GFP_KERNEL, "PIN%u", pin->number);
		if (!pindesc->name) {
			kfree(pindesc);
			return -ENOMEM;
		}
		pindesc->dynamic_name = true;
	}

	pindesc->drv_data = pin->drv_data;

	radix_tree_insert(&pctldev->pin_desc_tree, pin->number, pindesc);
	pr_debug("registered pin %d (%s) on %s\n",
		 pin->number, pindesc->name, pctldev->desc->name);
	return 0;
}