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
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;
struct pin_desc {char const* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int const) ; 
 struct pin_desc* pin_desc_get (struct pinctrl_dev*,unsigned int const) ; 

const char *pin_get_name(struct pinctrl_dev *pctldev, const unsigned pin)
{
	const struct pin_desc *desc;

	desc = pin_desc_get(pctldev, pin);
	if (!desc) {
		dev_err(pctldev->dev, "failed to get pin(%d) name\n",
			pin);
		return NULL;
	}

	return desc->name;
}