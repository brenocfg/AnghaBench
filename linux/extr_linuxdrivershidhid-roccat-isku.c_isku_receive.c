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
typedef  int /*<<< orphan*/  uint ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int roccat_common2_receive (struct usb_device*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isku_receive(struct usb_device *usb_dev, uint command,
		void *buf, uint size)
{
	return roccat_common2_receive(usb_dev, command, buf, size);
}