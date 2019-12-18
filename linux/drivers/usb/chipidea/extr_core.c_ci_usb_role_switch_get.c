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
struct device {int dummy; } ;
struct ci_hdrc {int /*<<< orphan*/  lock; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;

/* Variables and functions */
 int ci_role_to_usb_role (struct ci_hdrc*) ; 
 struct ci_hdrc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static enum usb_role ci_usb_role_switch_get(struct device *dev)
{
	struct ci_hdrc *ci = dev_get_drvdata(dev);
	enum usb_role role;
	unsigned long flags;

	spin_lock_irqsave(&ci->lock, flags);
	role = ci_role_to_usb_role(ci);
	spin_unlock_irqrestore(&ci->lock, flags);

	return role;
}