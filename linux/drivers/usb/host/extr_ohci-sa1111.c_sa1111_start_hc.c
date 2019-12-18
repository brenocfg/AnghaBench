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
struct sa1111_dev {scalar_t__ mapbase; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ USB_RESET ; 
 unsigned int USB_RESET_FORCEHCRESET ; 
 unsigned int USB_RESET_FORCEIFRESET ; 
 unsigned int USB_RESET_PWRCTRLLOW ; 
 unsigned int USB_RESET_PWRSENSELOW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ machine_is_assabet () ; 
 scalar_t__ machine_is_badge4 () ; 
 scalar_t__ machine_is_pfs168 () ; 
 scalar_t__ machine_is_xp860 () ; 
 int sa1111_enable_device (struct sa1111_dev*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int sa1111_start_hc(struct sa1111_dev *dev)
{
	unsigned int usb_rst = 0;
	int ret;

	dev_dbg(&dev->dev, "starting SA-1111 OHCI USB Controller\n");

	if (machine_is_xp860() ||
	    machine_is_assabet() ||
	    machine_is_pfs168() ||
	    machine_is_badge4())
		usb_rst = USB_RESET_PWRSENSELOW | USB_RESET_PWRCTRLLOW;

	/*
	 * Configure the power sense and control lines.  Place the USB
	 * host controller in reset.
	 */
	writel_relaxed(usb_rst | USB_RESET_FORCEIFRESET | USB_RESET_FORCEHCRESET,
		      dev->mapbase + USB_RESET);

	/*
	 * Now, carefully enable the USB clock, and take
	 * the USB host controller out of reset.
	 */
	ret = sa1111_enable_device(dev);
	if (ret == 0) {
		udelay(11);
		writel_relaxed(usb_rst, dev->mapbase + USB_RESET);
	}

	return ret;
}