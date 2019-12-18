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
struct usb_phy {int dummy; } ;
struct device {int dummy; } ;
typedef  enum usb_phy_type { ____Placeholder_usb_phy_type } usb_phy_type ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct usb_phy* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct usb_phy*) ; 
 int /*<<< orphan*/  devm_usb_phy_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct usb_phy**) ; 
 struct usb_phy** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct usb_phy**) ; 
 struct usb_phy* usb_get_phy (int) ; 

struct usb_phy *devm_usb_get_phy(struct device *dev, enum usb_phy_type type)
{
	struct usb_phy **ptr, *phy;

	ptr = devres_alloc(devm_usb_phy_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	phy = usb_get_phy(type);
	if (!IS_ERR(phy)) {
		*ptr = phy;
		devres_add(dev, ptr);
	} else
		devres_free(ptr);

	return phy;
}