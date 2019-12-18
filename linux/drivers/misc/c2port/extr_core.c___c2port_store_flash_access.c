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
struct c2port_device {int flash_access; int /*<<< orphan*/  access; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  C2PORT_FPCTL ; 
 int EBUSY ; 
 int /*<<< orphan*/  c2port_write_ar (struct c2port_device*,int /*<<< orphan*/ ) ; 
 int c2port_write_dr (struct c2port_device*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static ssize_t __c2port_store_flash_access(struct c2port_device *dev,
						int status)
{
	int ret;

	/* Check the device access status */
	if (!dev->access)
		return -EBUSY;

	dev->flash_access = !!status;

	/* If flash_access is off we have nothing to do... */
	if (dev->flash_access == 0)
		return 0;

	/* Target the C2 flash programming control register for C2 data
	 * register access */
	c2port_write_ar(dev, C2PORT_FPCTL);

	/* Write the first keycode to enable C2 Flash programming */
	ret = c2port_write_dr(dev, 0x02);
	if (ret < 0)
		return ret;

	/* Write the second keycode to enable C2 Flash programming */
	ret = c2port_write_dr(dev, 0x01);
	if (ret < 0)
		return ret;

	/* Delay for at least 20ms to ensure the target is ready for
	 * C2 flash programming */
	mdelay(25);

	return 0;
}