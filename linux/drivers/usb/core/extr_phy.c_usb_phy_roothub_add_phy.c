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
struct usb_phy_roothub {int /*<<< orphan*/  list; struct phy* phy; } ;
struct phy {int dummy; } ;
struct list_head {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 struct usb_phy_roothub* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy* devm_of_phy_get_by_index (struct device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int usb_phy_roothub_add_phy(struct device *dev, int index,
				   struct list_head *list)
{
	struct usb_phy_roothub *roothub_entry;
	struct phy *phy;

	phy = devm_of_phy_get_by_index(dev, dev->of_node, index);
	if (IS_ERR(phy)) {
		if (PTR_ERR(phy) == -ENODEV)
			return 0;
		else
			return PTR_ERR(phy);
	}

	roothub_entry = devm_kzalloc(dev, sizeof(*roothub_entry), GFP_KERNEL);
	if (!roothub_entry)
		return -ENOMEM;

	INIT_LIST_HEAD(&roothub_entry->list);

	roothub_entry->phy = phy;

	list_add_tail(&roothub_entry->list, list);

	return 0;
}