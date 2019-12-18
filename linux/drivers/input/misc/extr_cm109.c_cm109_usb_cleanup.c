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
struct cm109_dev {int /*<<< orphan*/  urb_ctl; int /*<<< orphan*/  urb_irq; int /*<<< orphan*/  irq_dma; scalar_t__ irq_data; int /*<<< orphan*/  udev; int /*<<< orphan*/  ctl_dma; scalar_t__ ctl_data; struct cm109_dev* ctl_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PKT_LEN ; 
 int /*<<< orphan*/  kfree (struct cm109_dev*) ; 
 int /*<<< orphan*/  usb_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cm109_usb_cleanup(struct cm109_dev *dev)
{
	kfree(dev->ctl_req);
	if (dev->ctl_data)
		usb_free_coherent(dev->udev, USB_PKT_LEN,
				  dev->ctl_data, dev->ctl_dma);
	if (dev->irq_data)
		usb_free_coherent(dev->udev, USB_PKT_LEN,
				  dev->irq_data, dev->irq_dma);

	usb_free_urb(dev->urb_irq);	/* parameter validation in core/urb */
	usb_free_urb(dev->urb_ctl);	/* parameter validation in core/urb */
	kfree(dev);
}