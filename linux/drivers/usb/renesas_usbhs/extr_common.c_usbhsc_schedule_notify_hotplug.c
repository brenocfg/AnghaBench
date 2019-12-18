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
struct usbhs_priv {int /*<<< orphan*/  notify_hotplug_work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  detection_delay ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 
 struct usbhs_priv* usbhs_pdev_to_priv (struct platform_device*) ; 

int usbhsc_schedule_notify_hotplug(struct platform_device *pdev)
{
	struct usbhs_priv *priv = usbhs_pdev_to_priv(pdev);
	int delay = usbhs_get_dparam(priv, detection_delay);

	/*
	 * This functions will be called in interrupt.
	 * To make sure safety context,
	 * use workqueue for usbhs_notify_hotplug
	 */
	schedule_delayed_work(&priv->notify_hotplug_work,
			      msecs_to_jiffies(delay));
	return 0;
}