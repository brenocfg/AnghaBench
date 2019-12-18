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
typedef  enum usb_phy_type { ____Placeholder_usb_phy_type } usb_phy_type ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct usb_phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct usb_phy*) ; 
 struct usb_phy* __usb_find_phy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_device (TYPE_2__*) ; 
 int /*<<< orphan*/  phy_list ; 
 int /*<<< orphan*/  phy_lock ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_phy_type_string (int) ; 

struct usb_phy *usb_get_phy(enum usb_phy_type type)
{
	struct usb_phy	*phy = NULL;
	unsigned long	flags;

	spin_lock_irqsave(&phy_lock, flags);

	phy = __usb_find_phy(&phy_list, type);
	if (IS_ERR(phy) || !try_module_get(phy->dev->driver->owner)) {
		pr_debug("PHY: unable to find transceiver of type %s\n",
			usb_phy_type_string(type));
		if (!IS_ERR(phy))
			phy = ERR_PTR(-ENODEV);

		goto err0;
	}

	get_device(phy->dev);

err0:
	spin_unlock_irqrestore(&phy_lock, flags);

	return phy;
}