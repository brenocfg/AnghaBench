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
struct yealink_dev {int /*<<< orphan*/  irq_dma; int /*<<< orphan*/  irq_data; int /*<<< orphan*/  udev; int /*<<< orphan*/  ctl_dma; int /*<<< orphan*/  ctl_data; struct yealink_dev* ctl_req; int /*<<< orphan*/  urb_ctl; int /*<<< orphan*/  urb_irq; scalar_t__ idev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PKT_LEN ; 
 int /*<<< orphan*/  input_free_device (scalar_t__) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct yealink_dev*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_cleanup(struct yealink_dev *yld, int err)
{
	if (yld == NULL)
		return err;

        if (yld->idev) {
		if (err)
			input_free_device(yld->idev);
		else
			input_unregister_device(yld->idev);
	}

	usb_free_urb(yld->urb_irq);
	usb_free_urb(yld->urb_ctl);

	kfree(yld->ctl_req);
	usb_free_coherent(yld->udev, USB_PKT_LEN, yld->ctl_data, yld->ctl_dma);
	usb_free_coherent(yld->udev, USB_PKT_LEN, yld->irq_data, yld->irq_dma);

	kfree(yld);
	return err;
}