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
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  DTK_ADDR_SPACE_XDATA ; 
 int read_download_mem (struct usb_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_ram(struct usb_device *dev, int start_address,
						int length, __u8 *buffer)
{
	return read_download_mem(dev, start_address, length,
					DTK_ADDR_SPACE_XDATA, buffer);
}