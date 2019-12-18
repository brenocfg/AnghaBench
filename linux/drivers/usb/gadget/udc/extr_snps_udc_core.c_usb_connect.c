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
struct udc {int connected; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udc_basic_init (struct udc*) ; 
 int /*<<< orphan*/  udc_enable_dev_setup_interrupts (struct udc*) ; 

__attribute__((used)) static void usb_connect(struct udc *dev)
{
	/* Return if already connected */
	if (dev->connected)
		return;

	dev_info(dev->dev, "USB Connect\n");

	dev->connected = 1;

	/* put into initial config */
	udc_basic_init(dev);

	/* enable device setup interrupts */
	udc_enable_dev_setup_interrupts(dev);
}