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
struct usb_configuration {int dummy; } ;
struct usb_composite_dev {int /*<<< orphan*/  lock; struct usb_configuration* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_config (struct usb_composite_dev*,struct usb_configuration*) ; 
 int /*<<< orphan*/  reset_config (struct usb_composite_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void usb_remove_config(struct usb_composite_dev *cdev,
		      struct usb_configuration *config)
{
	unsigned long flags;

	spin_lock_irqsave(&cdev->lock, flags);

	if (cdev->config == config)
		reset_config(cdev);

	spin_unlock_irqrestore(&cdev->lock, flags);

	remove_config(cdev, config);
}