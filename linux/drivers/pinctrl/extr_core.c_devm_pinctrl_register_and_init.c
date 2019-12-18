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
struct pinctrl_dev {int dummy; } ;
struct pinctrl_desc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_pinctrl_dev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct pinctrl_dev**) ; 
 struct pinctrl_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct pinctrl_dev**) ; 
 int pinctrl_register_and_init (struct pinctrl_desc*,struct device*,void*,struct pinctrl_dev**) ; 

int devm_pinctrl_register_and_init(struct device *dev,
				   struct pinctrl_desc *pctldesc,
				   void *driver_data,
				   struct pinctrl_dev **pctldev)
{
	struct pinctrl_dev **ptr;
	int error;

	ptr = devres_alloc(devm_pinctrl_dev_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	error = pinctrl_register_and_init(pctldesc, dev, driver_data, pctldev);
	if (error) {
		devres_free(ptr);
		return error;
	}

	*ptr = *pctldev;
	devres_add(dev, ptr);

	return 0;
}