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
struct TYPE_2__ {struct device* parent; } ;
struct extcon_dev {TYPE_1__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct extcon_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct extcon_dev*) ; 
 int /*<<< orphan*/  devm_extcon_dev_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct extcon_dev**) ; 
 struct extcon_dev** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct extcon_dev**) ; 
 struct extcon_dev* extcon_dev_allocate (unsigned int const*) ; 

struct extcon_dev *devm_extcon_dev_allocate(struct device *dev,
					const unsigned int *supported_cable)
{
	struct extcon_dev **ptr, *edev;

	ptr = devres_alloc(devm_extcon_dev_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	edev = extcon_dev_allocate(supported_cable);
	if (IS_ERR(edev)) {
		devres_free(ptr);
		return edev;
	}

	edev->dev.parent = dev;

	*ptr = edev;
	devres_add(dev, ptr);

	return edev;
}