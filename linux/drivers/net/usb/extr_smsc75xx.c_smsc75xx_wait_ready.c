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
typedef  int u32 ;
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PMT_CTL ; 
 int PMT_CTL_DEV_RDY ; 
 int __smsc75xx_read_reg (struct usbnet*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int smsc75xx_wait_ready(struct usbnet *dev, int in_pm)
{
	int timeout = 0;

	do {
		u32 buf;
		int ret;

		ret = __smsc75xx_read_reg(dev, PMT_CTL, &buf, in_pm);

		if (ret < 0) {
			netdev_warn(dev->net, "Failed to read PMT_CTL: %d\n", ret);
			return ret;
		}

		if (buf & PMT_CTL_DEV_RDY)
			return 0;

		msleep(10);
		timeout++;
	} while (timeout < 100);

	netdev_warn(dev->net, "timeout waiting for device ready\n");
	return -EIO;
}