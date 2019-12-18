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
struct usb_phy {TYPE_2__* dev; } ;
struct phy_devm {struct notifier_block* nb; struct usb_phy* phy; } ;
struct notifier_block {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct usb_phy*) ; 
 struct usb_phy* __of_usb_find_phy (struct device_node*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  devm_usb_phy_release2 ; 
 int /*<<< orphan*/  devres_add (struct device*,struct phy_devm*) ; 
 struct phy_devm* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct phy_devm*) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  phy_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_register_notifier (struct usb_phy*,struct notifier_block*) ; 

struct  usb_phy *devm_usb_get_phy_by_node(struct device *dev,
					  struct device_node *node,
					  struct notifier_block *nb)
{
	struct usb_phy	*phy = ERR_PTR(-ENOMEM);
	struct phy_devm	*ptr;
	unsigned long	flags;

	ptr = devres_alloc(devm_usb_phy_release2, sizeof(*ptr), GFP_KERNEL);
	if (!ptr) {
		dev_dbg(dev, "failed to allocate memory for devres\n");
		goto err0;
	}

	spin_lock_irqsave(&phy_lock, flags);

	phy = __of_usb_find_phy(node);
	if (IS_ERR(phy)) {
		devres_free(ptr);
		goto err1;
	}

	if (!try_module_get(phy->dev->driver->owner)) {
		phy = ERR_PTR(-ENODEV);
		devres_free(ptr);
		goto err1;
	}
	if (nb)
		usb_register_notifier(phy, nb);
	ptr->phy = phy;
	ptr->nb = nb;
	devres_add(dev, ptr);

	get_device(phy->dev);

err1:
	spin_unlock_irqrestore(&phy_lock, flags);

err0:

	return phy;
}