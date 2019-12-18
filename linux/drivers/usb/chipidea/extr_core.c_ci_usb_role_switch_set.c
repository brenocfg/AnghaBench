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
struct device {int dummy; } ;
struct ci_hdrc_cable {int changed; int connected; } ;
struct ci_hdrc {int /*<<< orphan*/  dev; int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; TYPE_1__* platdata; scalar_t__ wq; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;
struct TYPE_2__ {struct ci_hdrc_cable id_extcon; struct ci_hdrc_cable vbus_extcon; } ;

/* Variables and functions */
 int USB_ROLE_DEVICE ; 
 int USB_ROLE_HOST ; 
 int USB_ROLE_NONE ; 
 int /*<<< orphan*/  ci_irq (int /*<<< orphan*/ ,struct ci_hdrc*) ; 
 int ci_role_to_usb_role (struct ci_hdrc*) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  flush_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ci_usb_role_switch_set(struct device *dev, enum usb_role role)
{
	struct ci_hdrc *ci = dev_get_drvdata(dev);
	struct ci_hdrc_cable *cable = NULL;
	enum usb_role current_role = ci_role_to_usb_role(ci);
	unsigned long flags;

	if (current_role == role)
		return 0;

	pm_runtime_get_sync(ci->dev);
	/* Stop current role */
	spin_lock_irqsave(&ci->lock, flags);
	if (current_role == USB_ROLE_DEVICE)
		cable = &ci->platdata->vbus_extcon;
	else if (current_role == USB_ROLE_HOST)
		cable = &ci->platdata->id_extcon;

	if (cable) {
		cable->changed = true;
		cable->connected = false;
		ci_irq(ci->irq, ci);
		spin_unlock_irqrestore(&ci->lock, flags);
		if (ci->wq && role != USB_ROLE_NONE)
			flush_workqueue(ci->wq);
		spin_lock_irqsave(&ci->lock, flags);
	}

	cable = NULL;

	/* Start target role */
	if (role == USB_ROLE_DEVICE)
		cable = &ci->platdata->vbus_extcon;
	else if (role == USB_ROLE_HOST)
		cable = &ci->platdata->id_extcon;

	if (cable) {
		cable->changed = true;
		cable->connected = true;
		ci_irq(ci->irq, ci);
	}
	spin_unlock_irqrestore(&ci->lock, flags);
	pm_runtime_put_sync(ci->dev);

	return 0;
}