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
struct usbhs_priv {int dummy; } ;
struct usbhs_irq_state {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct platform_device* usbhs_priv_to_pdev (struct usbhs_priv*) ; 
 int /*<<< orphan*/  usbhsc_schedule_notify_hotplug (struct platform_device*) ; 

__attribute__((used)) static int usbhsm_autonomy_irq_vbus(struct usbhs_priv *priv,
				    struct usbhs_irq_state *irq_state)
{
	struct platform_device *pdev = usbhs_priv_to_pdev(priv);

	usbhsc_schedule_notify_hotplug(pdev);

	return 0;
}