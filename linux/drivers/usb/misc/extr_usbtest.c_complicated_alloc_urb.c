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
struct usb_device {int dummy; } ;
struct urb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URB_NO_TRANSFER_DMA_MAP ; 
 int /*<<< orphan*/  complicated_callback ; 
 struct urb* usbtest_alloc_urb (struct usb_device*,int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct urb *complicated_alloc_urb(
	struct usb_device	*udev,
	int			pipe,
	unsigned long		bytes,
	u8			bInterval)
{
	return usbtest_alloc_urb(udev, pipe, bytes, URB_NO_TRANSFER_DMA_MAP, 0,
			bInterval, complicated_callback);
}