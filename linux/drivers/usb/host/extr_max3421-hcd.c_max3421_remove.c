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
struct TYPE_2__ {int /*<<< orphan*/ * controller; } ;
struct usb_hcd {TYPE_1__ self; } ;
struct spi_device {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct max3421_hcd {int /*<<< orphan*/  lock; struct max3421_hcd* next; int /*<<< orphan*/  spi_thread; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,struct spi_device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct usb_hcd*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct max3421_hcd* max3421_hcd_list ; 
 struct usb_hcd* max3421_to_hcd (struct max3421_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_put_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  usb_remove_hcd (struct usb_hcd*) ; 

__attribute__((used)) static int
max3421_remove(struct spi_device *spi)
{
	struct max3421_hcd *max3421_hcd = NULL, **prev;
	struct usb_hcd *hcd = NULL;
	unsigned long flags;

	for (prev = &max3421_hcd_list; *prev; prev = &(*prev)->next) {
		max3421_hcd = *prev;
		hcd = max3421_to_hcd(max3421_hcd);
		if (hcd->self.controller == &spi->dev)
			break;
	}
	if (!max3421_hcd) {
		dev_err(&spi->dev, "no MAX3421 HCD found for SPI device %p\n",
			spi);
		return -ENODEV;
	}

	usb_remove_hcd(hcd);

	spin_lock_irqsave(&max3421_hcd->lock, flags);

	kthread_stop(max3421_hcd->spi_thread);
	*prev = max3421_hcd->next;

	spin_unlock_irqrestore(&max3421_hcd->lock, flags);

	free_irq(spi->irq, hcd);

	usb_put_hcd(hcd);
	return 0;
}