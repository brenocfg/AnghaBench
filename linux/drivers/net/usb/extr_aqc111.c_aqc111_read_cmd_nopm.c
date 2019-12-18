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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int USB_DIR_IN ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int usbnet_read_cmd_nopm (struct usbnet*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqc111_read_cmd_nopm(struct usbnet *dev, u8 cmd, u16 value,
				u16 index, u16 size, void *data)
{
	int ret;

	ret = usbnet_read_cmd_nopm(dev, cmd, USB_DIR_IN | USB_TYPE_VENDOR |
				   USB_RECIP_DEVICE, value, index, data, size);

	if (unlikely(ret < 0))
		netdev_warn(dev->net,
			    "Failed to read(0x%x) reg index 0x%04x: %d\n",
			    cmd, index, ret);

	return ret;
}