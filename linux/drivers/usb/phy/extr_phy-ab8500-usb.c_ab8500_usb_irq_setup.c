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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ab8500_usb {int flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ ; 
 int AB8500_USB_FLAG_USE_LINK_STATUS_IRQ ; 
 int AB8500_USB_FLAG_USE_VBUS_DET_IRQ ; 
 int IRQF_NO_SUSPEND ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  ab8500_usb_disconnect_irq ; 
 int /*<<< orphan*/  ab8500_usb_link_status_irq ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,struct ab8500_usb*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 

__attribute__((used)) static int ab8500_usb_irq_setup(struct platform_device *pdev,
		struct ab8500_usb *ab)
{
	int err;
	int irq;

	if (ab->flags & AB8500_USB_FLAG_USE_LINK_STATUS_IRQ) {
		irq = platform_get_irq_byname(pdev, "USB_LINK_STATUS");
		if (irq < 0)
			return irq;
		err = devm_request_threaded_irq(&pdev->dev, irq, NULL,
				ab8500_usb_link_status_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-link-status", ab);
		if (err < 0) {
			dev_err(ab->dev, "request_irq failed for link status irq\n");
			return err;
		}
	}

	if (ab->flags & AB8500_USB_FLAG_USE_ID_WAKEUP_IRQ) {
		irq = platform_get_irq_byname(pdev, "ID_WAKEUP_F");
		if (irq < 0)
			return irq;
		err = devm_request_threaded_irq(&pdev->dev, irq, NULL,
				ab8500_usb_disconnect_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-id-fall", ab);
		if (err < 0) {
			dev_err(ab->dev, "request_irq failed for ID fall irq\n");
			return err;
		}
	}

	if (ab->flags & AB8500_USB_FLAG_USE_VBUS_DET_IRQ) {
		irq = platform_get_irq_byname(pdev, "VBUS_DET_F");
		if (irq < 0)
			return irq;
		err = devm_request_threaded_irq(&pdev->dev, irq, NULL,
				ab8500_usb_disconnect_irq,
				IRQF_NO_SUSPEND | IRQF_SHARED | IRQF_ONESHOT,
				"usb-vbus-fall", ab);
		if (err < 0) {
			dev_err(ab->dev, "request_irq failed for Vbus fall irq\n");
			return err;
		}
	}

	return 0;
}