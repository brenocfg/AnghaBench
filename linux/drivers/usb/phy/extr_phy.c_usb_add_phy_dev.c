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
struct usb_phy {int /*<<< orphan*/  head; int /*<<< orphan*/  notifier; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_list ; 
 int /*<<< orphan*/  phy_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_add_extcon (struct usb_phy*) ; 
 int /*<<< orphan*/  usb_charger_init (struct usb_phy*) ; 

int usb_add_phy_dev(struct usb_phy *x)
{
	unsigned long flags;
	int ret;

	if (!x->dev) {
		dev_err(x->dev, "no device provided for PHY\n");
		return -EINVAL;
	}

	usb_charger_init(x);
	ret = usb_add_extcon(x);
	if (ret)
		return ret;

	ATOMIC_INIT_NOTIFIER_HEAD(&x->notifier);

	spin_lock_irqsave(&phy_lock, flags);
	list_add_tail(&x->head, &phy_list);
	spin_unlock_irqrestore(&phy_lock, flags);

	return 0;
}